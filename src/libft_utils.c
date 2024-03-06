/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/05 16:43:19 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	int		l;
	int		i;
	char	*k;

	i = 0;
	l = ft_strlen((char *)s);
	k = malloc((l + 1) * (sizeof(const char)));
	if (k == NULL)
		return (NULL);
	while (s[i])
	{
		k[i] = s[i];
		i++;
	}
	k[i] = '\0';
	return (k);
}

char	*ft_strdupi(char *original, int *index, int size)
{
	char	*copy;
	int		i;

	if (*index != 0 && original[*index] == '|')
		*index = *index + 1;
	while (is_whitespace(original[*index]))
	{
		*index = *index + 1;
		--size;
	}
	copy = malloc((size + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = original[*index];
		*index = *index + 1;
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
