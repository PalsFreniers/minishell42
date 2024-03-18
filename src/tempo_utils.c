/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tempo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/05 16:56:41 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_heredocs(char *command, int *i, t_com *comm, int *j)
{
	int	index_last_hd;

	index_last_hd = 0;
	if (bis_quote(command, *i))
		find_next_quote(command, i, command[*i], 1);
	if (command[*i] == '<' && command[*i + 1] == '<')
	{
		comm->expand_hd = true;
		*i = *i + 2;
		if (check_for_next_char(command, *i) == '\"')
			comm->expand_hd = false;
		comm->here_doc_delimiter[*j] = get_the_next_arg(command, i, NULL);
		index_last_hd = *i;
		*j = *j + 1;
	}
	else
		*i = *i + 1;
	return (index_last_hd);
}
