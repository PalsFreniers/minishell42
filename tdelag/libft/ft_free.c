/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:23:50 by tdelage           #+#    #+#             */
/*   Updated: 2024/01/31 08:11:16 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

void	ft_free(enum e_freeable which, ...)
{
	va_list			ap;
	enum e_freeable	w;

	w = which;
	va_start(ap, which);
	while (w != FT_NONE)
	{
		if (w == FT_PTR)
			free(va_arg(ap, void *));
		else if (w == FT_ARENA)
			ft_arena_destroy(va_arg(ap, struct s_arena *));
		w = va_arg(ap, enum e_freeable);
	}
}
