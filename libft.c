/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/13 10:41:20 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strbackslashn(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\n')
		i++;
	return (i);
}

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

char	*ft_strdup_env(const char *s, char *cut)
{
	int		l;
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	l = ft_strlen((char *)s) - (ft_strlen(cut) + 1);
	result = malloc((l + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s[i] && cut[i] && s[i] == cut[i])
		i++;
	if (s[i] == '=')
		i++;
	while (s[i])
		result[j++] = s[i++];
	result[j] = '\0';
	return (result);
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
