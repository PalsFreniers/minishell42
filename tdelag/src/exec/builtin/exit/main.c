/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:25:23 by tdelage           #+#    #+#             */
/*   Updated: 2024/02/28 17:10:54 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"
#include <stdlib.h>

t_bool	b_is_correct(char *tmp, int i)
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

int	b_exit_checks(char **arguments, int argc, t_u64 ret)
{
	if (ret > MIN_I64)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arguments[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	if (argc > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else
		return (ft_atol(arguments[1]));
}

int	b_exit(int argc, char **argv, char **envp)
{
	int		i;
	char	*tmp;
	t_u64	ret;

        (void)envp;
	i = 0;
	if (argc > 1)
	{
		tmp = argv[1];
		if (tmp[0] == '-' || tmp[0] == '+')
			i++;
		if (!b_is_correct(tmp, i))
			return (2);
		ret = ft_atol(tmp + i);
		return (b_exit_checks(argv, argc, ret));
	}
	return (0);
}
