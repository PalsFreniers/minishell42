/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/29 11:22:25 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    ft_strcmp(char *modele, char *compared)
{
	int	i;

	i = 0;
	if (!compared)
		return (false);
	while (modele[i])
	{
		if (!compared[i])
		    return (false);
		if (compared[i] != modele[i])
			return (false);
		++i;
	}
	if (compared[i])
		return (false);
	return (true);
}

char	*ft_strcatslash(char *begin, char *end)
{
	int		i;
	int		j;
	int		l;
	char	*result;

	l = ft_strlen(begin) + ft_strlen(end);
	result = malloc((l + 2) * sizeof(char));
	i = 0;
	j = 0;
	while (begin[i])
		result[j++] = begin[i++];
	i = 0;
	result[j++] = '/';
	while (end[i])
		result[j++] = end[i++];
	result[j] = 0;
	return (result);
}

void	ft_str_append(char **begin, int *j, char *end)
{
	int	i;

	i = 0;
	while (end[i])
	{
		(*begin)[*j] = end[i];
		i++;
		*j = *j + 1;
	}
}

int	is_parasit(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

void	look_for_heredoc(char *command, int *i, t_com *comm)
{
	if (is_quote(command[*i]))
		find_next_quote(command, i, command[*i], 1);
	else if (command[*i] == '<' && command[*i + 1] == '<')
	{
		comm->has_heredoc++;
		*i = *i + 2;
	}
	else
		*i = *i + 1;
}
