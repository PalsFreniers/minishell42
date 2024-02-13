/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:13:48 by tdelage           #+#    #+#             */
/*   Updated: 2024/01/25 23:15:28 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

struct s_string	ft_string_create(char *str, size_t size)
{
	struct s_string	string;

	string.ptr = str;
	string.len = size;
	return (string);
}

struct s_string	ft_string_from_cstr(char *str)
{
	return (ft_string_create(str, ft_strlen(str)));
}
