/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:38:11 by tdelage           #+#    #+#             */
/*   Updated: 2024/01/25 23:41:34 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMPLEX_H
# define FT_COMPLEX_H

# include "libft.h"

struct s_complex	ft_complex_create(double real, double imag)
{
	struct s_complex	clx;

	clx.r = real;
	clx.i = imag;
	return (clx);
}

#endif // FT_COMPLEX_H
