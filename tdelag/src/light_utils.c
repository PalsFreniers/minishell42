/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/03 23:03:46 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_for_next_char(char *command, int i)
{
	++i;
	while (command[i] && is_whitespace(command[i]))
		++i;
	return (command[i]);
}

int	ft_strlen_char_ss(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

char	**ft_strdup_char_star(char **to_dup)
{
	char	**copy;
	int		l;
	int		i;

	l = ft_strlen_char_ss(to_dup);
	copy = malloc((l + 1) * sizeof(char *));
	i = 0;
	while (i < l)
	{
		copy[i] = ft_strdup(to_dup[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
