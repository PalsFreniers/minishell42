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

char	*entry_to_text(t_entry entry)
{
	static char	*table[] = {
		"ENTRY_HEREDOC",
		"ENTRY_INPUT",
		"ENTRY_PIPE",
		"NO_ENTRY",
		"HD_ERROR",
	};

	return (table[entry]);
}

char	*exit_to_text(t_exit exit)
{
	static char	*table[] = {
		"EXIT_OUTPUT",
		"EXIT_PIPE",
		"EXIT_STDOUT",
	};

	return (table[exit]);
}

int	get_heredocs(char *command, int *i, t_com *comm, int *j)
{
	int	index_last_hd;

	index_last_hd = 0;
	if (char_is_quote(command[*i]))
		find_next_quote(command, i, command[*i]);
	if (command[*i] == '<' && command[*i + 1] == '<')
	{
		if (check_for_error_hd(command, *i + 2, comm, 0))
		{
			skip_to_the_next_word(command, i);
			while (command[*i] == '<')
				*i = *i + 1;
		}
		else
		{
			*i = *i + 2;
			comm->here_doc_delimiter[*j] = get_the_next_arg(command, i);
			index_last_hd = *i;
			*j = *j + 1;
		}
	}
	else
		*i = *i + 1;
	return (index_last_hd);
}
