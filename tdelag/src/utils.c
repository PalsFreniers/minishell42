/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 11:10:58 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_both(int *counter, int *index)
{
	*counter = *counter + 1;
	*index = *index + 1;
}

void	free_all(char **commands)
{
	int	i;

	i = 0;
	if (commands)
	{
		while (commands[i])
		{
			free(commands[i]);
			i++;
		}
		free(commands);
	}
}

void	dup_and_get_next(char **copy, int *i, char **paste, int *j)
{
	(*paste)[*j] = (*copy)[*i];
	increment_both(i, j);
}

void	skip_undesired(char *command, int *i, int *reset, int *c)
{
	if (is_whitespace(command[*i]))
	{
		*reset = 1;
		while (command[*i] && is_whitespace(command[*i]))
			*i = *i + 1;
	}
	else if (is_parasit(command[*i]))
	{
		while (is_parasit(command[*i]))
			*i = *i + 1;
		skip_the_next_word(command, i);
	}
	else if (is_quote(command[*i]))
	{
		if (*reset == 1)
		{
			*c = *c + 1;
			*reset = 0;
		}
		find_next_quote(command, i, command[*i], 1);
	}
}
