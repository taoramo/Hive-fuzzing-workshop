/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:10:29 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 17:10:30 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	push_matches(t_vec *dst, char *arg, DIR *ptr, int redirect)
{
	struct dirent	*ep;
	int				j;
	char			*path;

	ep = readdir(ptr);
	j = 0;
	while (ep)
	{
		if (is_wildcard_match(ep->d_name, arg))
		{
			path = ft_strdup(ep->d_name);
			if (!path)
				return (exp_wc_err(dst, "error allocating memory"));
			if (!j && redirect && vec_push(dst, &path) < 0)
				return (exp_wc_err(dst, "error allocating memory"));
			if (j > 0 && redirect)
				return (ambiguous_wildcard(arg));
			if (!redirect && ft_strlen(path) && vec_push(dst, &path) < 0)
				return (exp_wc_err(dst, "error parsing wildcard"));
			j++;
		}
		ep = readdir(ptr);
	}
	closedir(ptr);
	return (after_wildcard_pushing(dst, arg, j, redirect));
}

char	*skip_redirect(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && (arg[i] == '<' || arg[i] == '>' || ft_isspace(arg[i])))
		i++;
	return (&arg[i]);
}

int	add_redirect_char(t_vec *dst, char *arg)
{
	char	*str;
	char	*last;

	last = *(char **)vec_get(dst, dst->len - 1);
	if (!ft_strncmp(arg, "<<", 2))
		str = ft_strjoin("<< ", last);
	if (!ft_strncmp(arg, "< ", 2))
		str = ft_strjoin("< ", last);
	if (!ft_strncmp(arg, ">>", 2))
		str = ft_strjoin(">> ", last);
	if (!ft_strncmp(arg, "> ", 2))
		str = ft_strjoin("> ", last);
	if (!str)
		return (-1);
	if (vec_push(dst, &str) < 0)
		return (-1);
	vec_remove(dst, 0);
	free(last);
	return (0);
}

int	push_expanded(t_vec *dst, char **strs, int i)
{
	DIR				*ptr;
	struct dirent	*ep;
	int				redirect;
	int				result;

	ptr = opendir("./");
	ep = readdir(ptr);
	ep = readdir(ptr);
	(void)ep;
	if (!ptr)
		return (exp_wc_err(dst, "error opening directory"));
	redirect = is_rdrct(strs[i]);
	if (redirect)
		result = push_matches(dst, skip_redirect(strs[i]), ptr, redirect);
	else
		result = push_matches(dst, strs[i], ptr, redirect);
	if (redirect && result == 1 && add_redirect_char(dst, strs[i]) < 0)
		return (-1);
	if (redirect && !result && vec_push(dst, &strs[i]) < 0)
		return (-1);
	return (0);
}

int	push_argv_elem(t_vec *dst, t_vec *argv, int i)
{
	char			**strs;

	strs = (char **)argv->memory;
	if (vec_push(dst, &strs[i]) < 0)
		return (exp_wc_err(dst, "error allocating memory"));
	return (0);
}

int	expand_star(t_vec *argv)
{
	t_vec			dst;
	t_vec			newargv;
	size_t			i;
	char			**strs;

	if (vec_new(&dst, 32, sizeof(char *)) < 0)
		return (ft_error("minishell: error allocating memory"));
	if (vec_new(&newargv, 32, sizeof(char *)) < 0)
		return (ft_error("minishell: error allocating memory"));
	i = 0;
	strs = (char **)argv->memory;
	while (i < argv->len)
	{
		if (ft_strchr(strs[i], '*') && !ft_is_inside(strs[i], ft_strchr(strs[i], '*') - strs[i], '"') && !ft_is_inside(strs[i], ft_strchr(strs[i], '*') - strs[i], 39))
		{
			if (push_expanded(&dst, strs, i) < 0)
				return (ft_error("minishell: error creating argv"));
		}
		else if (push_argv_elem(&newargv, argv, i) < 0)
			return (-1);
		i++;
	}
	vec_append(&newargv, &dst);
	vec_free(argv);
	ft_memcpy(argv, &newargv, sizeof(t_vec));
	vec_free(&dst);
	return (0);
}
