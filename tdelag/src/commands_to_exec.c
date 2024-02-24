/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_to_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 11:08:48 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_disection(char *command, t_com *comm)
{
	int	i;
	int	last_heredoc_i;

	i = 0;
	comm->program = get_the_next_arg(command, &i);
<<<<<<< HEAD:tdelag/src/commands_to_exec.c
=======
	comm->has_program = true;
	if (!command[i] && !(ft_strlen(comm->program)) && \
		(!(is_quote(command[i - 1])) && !(is_quote(command[i - 2]))))
		comm->has_program = false;
>>>>>>> origin/werwer:src/commands_to_exec.c
	comm->arguments = get_the_arguments(command, &i, comm->program);
	last_heredoc_i = has_heredoc(command, comm);
	if (!comm->has_heredoc)
		last_heredoc_i = -1;
	has_input(command, comm, last_heredoc_i, 0);
	has_output(command, comm);
	return (1);
}
