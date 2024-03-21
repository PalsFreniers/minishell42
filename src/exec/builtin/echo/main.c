/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:18:51 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/08 04:24:30 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"

t_bool	b_echo_option(char *arg, char *trailing)
{
	int	i;

	if (arg[0] != '-')
		return (FALSE);
	i = 1;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0' && i > 1)
	{
		*trailing = 0;
		return (TRUE);
	}
	return (FALSE);
}

int	get_options(int argc, char **args, char *trailing)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (!b_echo_option(args[i], trailing))
			break ;
		i++;
	}
	return (i);
}

int	b_echo(int count, char **args, char **envp)
{
	int		i;
	char	trailing;

	(void)envp;
	i = 1;
	trailing = '\n';
	if (count > 1)
		i += get_options(count - 1, args + 1, &trailing);
	while (i < count)
	{
		ft_printf("%s", args[i]);
		if (i < count - 1)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (trailing)
		ft_putchar_fd(trailing, 1);
	return (0);
}
