/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/06 12:39:00 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treat_append_output(char *command, t_com *comm, int *i)
{
	char	*tempo;
	int		fd;

	*i = *i + 1;
	tempo = get_the_next_arg(command, i, NULL);
	fd = open(tempo, O_CREAT | O_RDWR | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		comm->error = tempo;
		return (1);
	}
	free(tempo);
	close(fd);
	return (0);
}

bool	check_invalid_out(char *command, t_com *comm, int *i)
{
	char	*tempo;
	int		fd;

	*i = *i + 1;
	if (command[*i] == '>')
	{
		if (treat_append_output(command, comm, i))
			return (true);
	}
	else
	{
		tempo = get_the_next_arg(command, i, NULL);
		fd = open(tempo, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd < 0)
		{
			comm->error = tempo;
			return (true);
		}
		free(tempo);
		close(fd);
	}
	return (false);
}

bool	check_invalid_in(char *command, t_com *comm, int *i)
{
	char	*tempo;
	int		fd;

	*i = *i + 1;
	if (command[*i] == '<')
	{
		*i = *i + 1;
		skip_the_next_word(command, i);
		return (false);
	}
	tempo = get_the_next_arg(command, i, NULL);
	fd = open(tempo, O_RDONLY);
	if (fd < 0)
	{
		comm->error = tempo;
		return (true);
	}
	free(tempo);
	close(fd);
	return (false);
}

bool	check_invalid_in_out(char *command, t_com *comm, int i)
{
	while (command[i])
	{
		if (is_quote(command[i]))
		{
			find_next_quote(command, &i, command[i], 1);
		}
		else if (command[i] == '>')
		{
			if (check_invalid_out(command, comm, &i))
				return (true);
		}
		else if (command[i] == '<')
		{
			if (check_invalid_in(command, comm, &i))
				return (true);
		}
		else
		{
			i = i + 1;
		}
	}
	return (false);
}
