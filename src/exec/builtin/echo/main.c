/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:18:51 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/05 23:14:17 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"

int	b_echo(int count, char **args, char **envp)
{
	int		i;
	char	trailing;

	(void)envp;
	i = 1;
	trailing = '\n';
	if (count > 1 && ft_strequ(args[1], "-n"))
	{
		trailing = '\0';
		i++;
	}
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
