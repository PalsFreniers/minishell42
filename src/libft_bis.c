/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/05 14:05:16 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_strcmp(char *modele, char *compared)
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

void	free_double_char(char **to_free)
{
	int	i;

	i = 0;
	if (!to_free)
		return ;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}
