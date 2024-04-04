/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:00:36 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 17:00:37 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_wc	*init_i(t_wc *i)
{
	i->pindex = 0;
	i->sindex = 0;
	i->s_backtrack = -1;
	i->last_wildcard = -1;
	i->next_to_wildcard = -1;
	i->i = 0;
	return (i);
}

void	set_indeces_at_wc(t_wc *i)
{
	i->last_wildcard = i->pindex;
	i->next_to_wildcard = ++i->pindex;
	i->s_backtrack = i->sindex;
}

int	check_rest_p(char *p, size_t pindex)
{
	while (pindex < ft_strlen(p))
	{
		if (p[pindex] != '*' && !ft_is_inside(p, pindex, '"')
			&& !ft_is_inside(p, pindex, 39))
			return (0);
		pindex++;
	}
	return (1);
}

int	is_wildcard_match(char *s, char *p)
{
	t_wc	i;

	init_i(&i);
	while (i.sindex < ft_strlen(s))
	{
		if (i.pindex < ft_strlen(p) && p[i.pindex] == s[i.sindex])
		{
			++i.pindex;
			++i.sindex;
		}
		else if (i.pindex < ft_strlen(p) && p[i.pindex] == '*'
			&& !ft_is_inside(p, i.pindex, '"')
			&& !ft_is_inside(p, i.pindex, 39))
			set_indeces_at_wc(&i);
		else if (i.last_wildcard == -1)
			return (0);
		else
		{
			i.pindex = i.next_to_wildcard;
			i.sindex = ++i.s_backtrack;
		}
	}
	return (check_rest_p(p, i.pindex));
}

int	after_wildcard_pushing(t_vec *dst, char *arg, int j, int redirect)
{
	char	*ptr;

	if (!j && !redirect)
	{
		ptr = ft_strdup(arg);
		if (!ptr)
			return (-1);
		if (vec_push(dst, &ptr) < 0)
			return (-1);
	}
	else if (!redirect)
	{
		free(arg);
		vec_sort(dst, vec_sort_strncmp);
	}
	return (j);
}
