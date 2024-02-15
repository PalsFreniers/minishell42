/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 17:50:15 by dosokin          ###   ########.fr       */
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
	if (is_quote(command[length]))
	{
		gtnhl(command, &length);
		return (length + 1 - i);
	}
	while (command[length] && !(is_whitespace(command[length])))
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

	while (command[*i] && (is_whitespace(command[*i])))
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
	int	index_last_hd;
	int	j;

	j = 0;
	comm->here_doc_delimiter = malloc((comm->has_heredoc + 1) * sizeof(char *));
	while (command[i])
		index_last_hd = get_heredocs(command, &i, comm, &j);
	comm->here_doc_delimiter[j] = NULL;
	return (index_last_hd);
}

int	has_heredoc(char *command, t_com *comm)
{
	int	i;

	i = 0;
	comm->has_heredoc = 0;
	comm->here_doc_delimiter = NULL;
	while (command[i])
		look_for_heredoc(command, &i, comm);
	if (comm->has_heredoc)
	{
		comm->entry = ENTRY_HEREDOC;
		i = here_doc_init(comm, command, 0);
		if (i == -1)
			comm->entry = HD_ERROR;
	}
	return (i);
}
