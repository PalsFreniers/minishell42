/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 22:57:08 by tdelage           #+#    #+#             */
/*   Updated: 2024/01/25 23:37:11 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "types.h"
# include <stddef.h>

struct		s_string
{
	char	*ptr;
	size_t	len;
};

struct		s_arena
{
	void	*ptr;
	void	*current;
	size_t	size;
	t_bool	is_free;
};

struct		s_complex
{
	t_f64	r;
	t_f64	i;
};

#endif // STRUCTS_H
