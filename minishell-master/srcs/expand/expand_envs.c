/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:31:19 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/13 09:10:18 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(t_vec *str_vec, size_t start)
{
	size_t	i;
	char	c;

	i = 0;
	start++;
	while (start + i < str_vec->len)
	{
		c = *(char *)vec_get(str_vec, start + i);
		if (c == '\'' || c == '\"' || c == '$')
			return (ft_substr((char *) str_vec->memory, start, i));
		if (c == '*' && !ft_is_inside((char *) str_vec->memory, start + i, '\'') &&
				!ft_is_inside((char *) str_vec->memory, start + i, '\"'))
			return (ft_substr((char *) str_vec->memory, start, i));
		i++;
	}
	return (ft_substr((char *) str_vec->memory, start, i));
}

int	replace_vec_str(t_vec *str_vec, char *new, size_t i, size_t remove_len)
{
	size_t	j;
	
	j = 0;
	while (j < remove_len)
	{
		if (vec_remove(str_vec, i) == -1)
			return (-1);
		j++;
	}
	j = 0;
	while (new[j] != 0)
	{
		if (vec_insert(str_vec, &new[j], i + j) == -1)
			return (-1);
		j++;
	}
	return (1);
}

int	expand_substr_env(t_vec *str_vec, size_t *i, t_vec *env, int last_return)
{
	char	*env_name;
	char	*env_expanded;
	int		ret;
	
	if (*i + 1 >= str_vec->len)
		return (1);
	if (*(char *)vec_get(str_vec, *i + 1) == '?')
	{
		env_expanded = ft_itoa(last_return);
		ret = replace_vec_str(str_vec, env_expanded, *i, 2);
		*i += 1;
		free(env_expanded);
		return (ret);
	}
	env_name = get_env_name(str_vec, *i);
	if (env_name == 0)
		return (-1);
	env_expanded = ft_getenv(env_name, env);
	if (env_expanded == 0)
		env_expanded = ft_strdup("");
	ret = replace_vec_str(str_vec, env_expanded, *i, ft_strlen(env_name) + 1);
	*i += ft_strlen(env_expanded) - 1;
	free(env_name);
	free(env_expanded);
	return (ret);
}

int	expand_str_envs(char **str_ptr, t_vec *env, int last_return)
{
	t_vec	str_vec;
	size_t	i;

	if (vec_from(&str_vec, *str_ptr, ft_strlen(*str_ptr), sizeof(char)) < 0)
		return (-1);
	i = 0;
	while (i < str_vec.len)
	{
		if (*(char *)vec_get(&str_vec, i) == '\'')
		{
			i++;
			while (i < str_vec.len && *(char *)vec_get(&str_vec, i) != '\'')
				i++;
		}
		if (i < str_vec.len && *(char *)vec_get(&str_vec, i) == '$')
		{
			if (expand_substr_env(&str_vec, &i, env, last_return) == -1)
				return (-1);
		}
		i++;
	}
	free(*str_ptr);
	char n = 0;
	if (vec_push(&str_vec, &n) < 0)
		return (-1);
	*str_ptr = (char *) str_vec.memory;
	return (1);
}

int	expand_envs(t_vec *argv, t_vec *env, int last_return)
{
	char	**str_ptr;
	size_t	i;

	i = 0;
	while (i < argv->len)
	{
		str_ptr = (char **)vec_get(argv, i);
		if (ft_strchr(*str_ptr, '$') != 0)
			expand_str_envs(str_ptr, env, last_return);
		i++;
	}
	return (1);
}
