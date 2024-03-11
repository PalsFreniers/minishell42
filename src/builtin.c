/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:30:00 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/11 05:41:08 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_correct(char *tmp, int i)
{
	while (tmp[i])
	{
		if (!ft_isdigit(tmp[i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(tmp, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

struct s_mainloop	sb_exit_checks(t_com *command, int argc, t_u64 ret)
{
	if (ret > MIN_I64)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(command->arguments[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return ((struct s_mainloop){0, 2});
	}
	if (argc > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ((struct s_mainloop){1, 1});
	}
	else
		return ((struct s_mainloop){0, ft_atol(command->arguments[1])});
}

struct s_mainloop	sb_exit(t_com *command, int last)
{
	int		argc;
	int		i;
	char	*tmp;
	t_u64	ret;

	argc = ft_dt_len((void **)command->arguments);
	i = 0;
	printf("exit\n");
	g_signum = SIGTRAP;
	if (argc > 1)
	{
		tmp = command->arguments[1];
		if (tmp[0] == '-' || tmp[0] == '+')
			i++;
		if (!is_correct(tmp, i))
			return ((struct s_mainloop){0, 2});
		ret = ft_atol(command->arguments[1] + i);
		return (sb_exit_checks(command, argc, ret));
	}
	return ((struct s_mainloop){0, last});
}

struct s_mainloop	sb_unset(t_com *command, char ***envp)
{
	int	i;

	i = 0;
	while (command->arguments[++i])
		remove_one(command->arguments[i], envp);
	return ((struct s_mainloop){1, 0});
}

struct s_mainloop	print_export(char **envp)
{
	int	i;
	int	j;

	i = -1;
	envp = sort_env(envp);
	if (!envp)
		return ((struct s_mainloop){1, 1});
	while (envp[++i])
	{
		j = -1;
		ft_putstr_fd("declare -x ", 1);
		while (envp[i][++j] != '=' && envp[i][j])
			ft_putchar_fd(envp[i][j], 1);
		if (envp[i][j])
		{
			ft_putstr_fd("=\"", 1);
			print_escape(envp[i] + j + 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
	}
	free_dt((void **)envp);
	return ((struct s_mainloop){1, 0});
}
