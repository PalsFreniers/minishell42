/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 07:52:29 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/04 18:35:26 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_trim_space(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	return ((char *)str + i);
}

static int	ft_from_buff_to_i(char *tmp, int st_index, int sign)
{
	size_t	pow;
	size_t	ret;

	pow = 1;
	ret = 0;
	while (st_index-- > 0)
	{
		ret += (tmp[st_index] - '0') * pow;
		pow *= 10;
	}
	return (ret * sign);
}

int	ft_atoi(const char *str)
{
	char	tmp[32];
	int		sign;
	size_t	t;

	if (!str)
		return (0);
	str = ft_trim_space(str);
	sign = 1;
	t = 0;
	--str;
	if (*(++str) == '-')
		sign = -1;
	else if (*str == '+')
	{
		sign = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && t < 32)
	{
		tmp[t] = *str;
		t++;
		str++;
	}
	return (ft_from_buff_to_i(tmp, t, sign));
}

static t_i64	ft_from_buff_to_l(char *tmp, int st_index, int sign)
{
	size_t	pow;
	size_t	ret;

	pow = 1;
	ret = 0;
	while (st_index-- > 0)
	{
		ret += (tmp[st_index] - '0') * pow;
		pow *= 10;
	}
	return (ret * sign);
}

t_i64	ft_atol(const char *str)
{
	char	tmp[64];
	int		sign;
	size_t	t;

	str = ft_trim_space(str);
	sign = 1;
	t = 0;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		sign = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && t < 32)
	{
		tmp[t] = *str;
		t++;
		str++;
	}
	return (ft_from_buff_to_l(tmp, t, sign));
}
