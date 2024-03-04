/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_to_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/04 12:45:23 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_disection(char *command, t_com *comm)
{
	int	i;
	int	last_heredoc_i;

	i = 0;
	comm->has_program = true;
	comm->program = get_the_next_arg(command, &i, &comm->has_program);
	if (!comm->program)
		return (1);
	comm->arguments = get_the_arguments(command, &i, comm->program);
	if (!comm->arguments)
		return (1);
	last_heredoc_i = has_heredoc(command, comm);
	if (!comm->has_heredoc)
		last_heredoc_i = -1;
	has_input(command, comm, last_heredoc_i, 0);
	has_output(command, comm);
	return (0);
}
