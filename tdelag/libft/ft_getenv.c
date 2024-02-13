/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:33:15 by tdelage           #+#    #+#             */
/*   Updated: 2024/02/08 08:33:22 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strprefix(env[i], name) == 1)
			return (env[i] + ft_strlenc(env[i], '=') + 2);
		i++;
	}
	return (NULL);
}
