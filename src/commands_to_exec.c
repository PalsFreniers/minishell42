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
	if (comm->program)
		comm->arguments = get_the_arguments(command, &i, comm->program);
	last_heredoc_i = has_heredoc(command, comm);
	if (!comm->has_heredoc)
		last_heredoc_i = -1;
	has_input(command, comm, last_heredoc_i, 0);
	has_output(command, comm);
	if (comm->outkind == FILE_ERROR || comm->entry == HD_ERROR || comm->entry == INPUT_ERROR)
	{
		i = ft_strlen(command);
		free(comm->program);
		comm->program = get_the_next_arg(command, &i);
		free_double_char(comm->arguments);
		comm->arguments = get_the_arguments(command, &i, comm->program);
	}
	return (1);
}
