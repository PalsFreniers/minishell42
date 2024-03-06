/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 11:08:57 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	call_itoa(int i, int n, char **result)
{
	if (i / 10 > 0)
		call_itoa(i / 10, n - 1, result);
	(*result)[n] = ((i % 10) + '0');
}

int	get_int_length(int i)
{
	int	c;

	c = 1;
	while (i / 10 > 0)
	{
		i = i / 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int i)
{
	int		l;
	char	*result;
	int		sign;

	sign = 0;
	if (i < 0)
	{
		i = -i;
		sign = 1;
	}
	l = get_int_length(i);
	l += sign;
	result = malloc((l + 1) * sizeof(char));
	if (sign)
		result[0] = '-';
	call_itoa(i, l - 1, &result);
	result[l + sign] = '\0';
	return (result);
}
