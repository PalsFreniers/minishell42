/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 11:47:18 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gtnhl(char *command, int *length)
{
	*length = *length + 1;
	if (command[*length - 1] == '\'')
	{
		while (command[*length] != '\'')
			*length = *length + 1;
	}
	else if (command[*length - 1] == '\"')
	{
		while (command[*length] != '\"')
			*length = *length + 1;
	}
}

int	get_the_next_hd_length(char *command, int i)
{
	int	length;

	length = i;
	if (char_is_quote(command[length]))
	{
		gtnhl(command, &length);
		return (length + 1 - i);
	}
	while (command[length] && !(char_is_whitespace(command[length])))
	{
		if (command[length] == '<' && command[length + 1] == '<')
			return (length - i);
		++length;
	}
	return (length - i);
}

char	*get_the_next_heredoc(char *command, int *i)
{
	char	*argument;
	int		length;
	int		j;

	while (command[*i] && (char_is_whitespace(command[*i])))
		*i = *i + 1;
	length = get_the_next_hd_length(command, *i);
	argument = malloc((length + 1) * sizeof(char));
	j = 0;
	while (j < length)
	{
		argument[j] = command[*i];
		*i = *i + 1;
		j++;
	}
	argument[j] = 0;
	return (argument);
}

int	here_doc_init(t_com *comm, char *command, int i)
{
	int	j;
	int	index_last_hd;

	j = 0;
	comm->here_doc_delimiter = malloc((comm->has_heredoc + 1) * sizeof(char *));
	while (command[i])
	{
		if (char_is_quote(command[i]))
			find_next_quote(command, &i, command[i]);
		if (command[i] == '<' && command[i + 1] == '<')
		{
			if (check_for_error_hd(command, i + 2, comm))
			{
				skip_to_the_next_word(command, &i);
				while (command[i] == '<')
					++i;
			}
			else
			{
				i += 2;
				comm->here_doc_delimiter[j] = get_the_next_arg(command, &i);
				index_last_hd = i;
				++j;
			}
		}
		else
			++i;
	}
	comm->here_doc_delimiter[j] = NULL;
	return (index_last_hd);
}

int	has_heredoc(char *command, t_com *comm)
{
	int		i;

	i = 0;
	comm->has_heredoc = 0;
	comm->here_doc_delimiter = NULL;
	while (command[i])
	{
		if (char_is_quote(command[i]))
			find_next_quote(command, &i, command[i]);
		else if (command[i] == '<' && command[i + 1] == '<')
		{
			if (check_for_error_hd(command, i + 2, comm))
			{
				skip_to_the_next_word(command, &i);
				while (command[i] == '<')
					++i;
			}
			else
			{
				comm->has_heredoc++;
				i += 2;
			}
		}
		else
			++i;
	}
	if (comm->has_heredoc)
	{
		comm->entry = ENTRY_HEREDOC;
		i = here_doc_init(comm, command, 0);
        if (i == -1)
            comm->entry = HD_ERROR;
	}
	return (i);
}
