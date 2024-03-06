/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:53:37 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 18:16:14 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	deinit_cd_first(t_com *comm)
{
	int	j;

	j = 0;
	if (comm->program)
		free(comm->program);
	if (comm->arguments)
	{
		while (comm->arguments[j])
		{
			free(comm->arguments[j]);
			j++;
		}
		free(comm->arguments);
	}
	j = 0;
	if (comm->has_heredoc)
	{
		while (comm->here_doc_delimiter[j])
		{
			free(comm->here_doc_delimiter[j]);
			j++;
		}
		free(comm->here_doc_delimiter);
	}
}

void	deinit_cd_second(t_com *comm)
{
	if (comm->has_input)
		free(comm->input);
	if (comm->has_output)
		free(comm->output);
	if (comm->error)
		free(comm->error);
	comm->outkind = APPEND;
	free(comm);
}

void	deinit_commands_data(t_com **command_data)
{
	int	i;

	i = 0;
	while (command_data[i])
	{
		deinit_cd_first(command_data[i]);
		deinit_cd_second(command_data[i]);
		i++;
	}
	free(command_data);
}

void	*deinit_thgg(t_main *thgg)
{
	if (thgg->usr_input)
		free(thgg->usr_input);
	if (thgg->paths)
		free_double_char(thgg->paths);
	if (thgg->commands)
		free_double_char(thgg->commands);
	if (thgg->commands_data)
		deinit_commands_data(thgg->commands_data);
	free(thgg);
	thgg = NULL;
	return (NULL);
}
