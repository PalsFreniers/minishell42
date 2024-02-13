/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_and_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 18:15:57 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treat_input(char *command, t_com *comm, int *i, int last_index_hd)
{
	*i = *i + 1;
	if (comm->has_input)
	{
		if (comm->fd_input > 0)
			close(comm->fd_input);
		free(comm->input);
	}
	comm->has_input = true;
	if (*i > last_index_hd)
		comm->entry = ENTRY_INPUT;
	comm->input = get_the_next_arg(command, i);
	comm->fd_input = open(comm->input, O_RDONLY);
	if (comm->fd_input < 0 && !comm->error)
	{
		comm->error = ft_strdup((const char *)comm->input);
		return (1);
	}
	return (0);
}

void	has_input(char *command, t_com *comm, int last_index_hd, int i)
{
	int	c;

	c = 0;
	while (command[i])
	{
		if (char_is_quote(command[i]))
			find_next_quote(command, &i, command[i]);
		else if (command[i] == '<')
		{
			if (command[i + 1] == '<')
			{
				i += 2;
				skip_the_next_word(command, &i);
			}
			else if (check_for_next_char(command, i) == '<')
				manage_bracketed_input(command, &i, &c, comm);
			else if (check_for_next_char(command, i) == '\0')
				manage_empty_input(&i, comm);
			else if (treat_input(command, comm, &i, last_index_hd))
				break ;
		}
		else
			i = i + 1;
	}
}

int	treat_output_second(char *command, t_com *comm, int *i)
{
	int	c;

	c = 0;
	if (check_for_error_output(command, *i + 2))
	{
		if (manage_errored_output(command, i, &c, comm))
			return (1);
	}
	else
	{
		*i = *i + 2;
		comm->outkind = APPEND;
		comm->output = get_the_next_arg(command, i);
		comm->fd_output = open(comm->output, O_CREAT | O_RDWR | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	return (0);
}

void	treat_output_first(char *command, t_com *comm, int *i)
{
	if (comm->has_output)
	{
		if (comm->fd_output > 0)
			close(comm->fd_output);
		free(comm->output);
	}
	comm->has_output = true;
	if (command[*i + 1] == '>')
	{
		if (treat_output_second(command, comm, i))
			return ;
	}
	else
	{
		*i = *i + 1;
		comm->outkind = OVERWRITE;
		comm->output = get_the_next_arg(command, i);
		comm->fd_output = open(comm->output, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	comm->exit = EXIT_OUTPUT;
}

void	has_output(char *command, t_com *comm)
{
	int	i;

	i = 0;
	comm->has_output = false;
	comm->output = NULL;
	while (command[i])
	{
		if (char_is_quote(command[i]))
			find_next_quote(command, &i, command[i]);
		else if (command[i] == '>')
		{
			treat_output_first(command, comm, &i);
			if (comm->outkind == FILE_ERROR)
				return ;
		}
		else
			++i;
	}
}
