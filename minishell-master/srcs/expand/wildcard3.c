#include "minishell.h"

int	exp_wc_err(t_vec *new, char *msg)
{
	free_split_vec(new);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

int	expnd_rdrct(t_vec *dst, char *path, char *arg)
{
	char	*expanded;

	expanded = 0;
	if (arg[0] == '<')
		expanded = ft_strjoin("< ", path);
	if (arg[0] == '>')
		expanded = ft_strjoin("> ", path);
	if (!expanded)
		return (-1);
	free(path);
	free(arg);
	if (vec_push(dst, &expanded) < 0)
		return (-1);
	return (1);
}

int	ambiguous_wildcard(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && (arg[i] == '<' || arg[i] == '>' || ft_isspace(arg[i])))
		i++;
	ft_printf("minishell: %s: ambiguous wildcard\n", &arg[i]);
	return (-1);
}

int	is_rdrct(char *arg)
{
	if (arg[0] == '<' || arg[0] == '>')
		return (1);
	return (0);
}
