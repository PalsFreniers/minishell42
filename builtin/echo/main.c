/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:18:51 by tdelage           #+#    #+#             */
/*   Updated: 2024/02/08 08:29:57 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../libft/libft.h"

int	echo(int count, char **args)
{
	int		i;
	char	trailing;

	i = 1;
	trailing = '\n';
	if (count > 1 && ft_strncmp(args[1], "-n", 2) == 0)
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
	exit(0);
}
