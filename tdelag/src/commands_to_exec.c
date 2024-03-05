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

int treat_append_output(char *command, t_com *comm, int *i)
{
    char    *tempo;
    int     fd;

    *i = *i + 1;
    tempo = get_the_next_arg(command, i, NULL);
    fd = open(tempo, O_CREAT | O_RDWR | O_APPEND,
              S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0)
    {
        printf ("fd: %d tempo:'%s'\n", fd, tempo);
        comm->error = tempo;
        return (1);
    }
    free(tempo);
    close (fd);
    return (0);
}

bool check_invalid_in_out(char *command, t_com *comm, int i)
{
    int     fd;
    char    *tempo;

    while (command[i])
    {
        if (is_quote(command[i]))
            find_next_quote(command, &i, command[i], 1);
        else if (command[i] == '>')
        {
            i++;
            if (command[i] == '>')
            {
                if (treat_append_output(command, comm, &i))
                    return (true);
            }
            else
            {
                tempo = get_the_next_arg(command, &i, NULL);
                fd = open(tempo, O_CREAT | O_WRONLY | O_TRUNC,
                          S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                if (fd < 0)
                {
                    comm->error = tempo;
                    return (true);
                }
                free(tempo);
                close (fd);
            }
        }
        else if (command[i] == '<')
        {
            ++i;
            if (command[i] == '<')
            {
                ++i;
                skip_the_next_word(command, &i);
                continue ;
            }
            tempo = get_the_next_arg(command, &i, NULL);
            fd = open(tempo, O_RDONLY);
            if (fd < 0)
            {
                comm->error = tempo;
                return (true);
            }
            free(tempo);
            close (fd);
        }
        else
            i = i + 1;
    }
    return (false);
}

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
    if (check_invalid_in_out(command, comm, 0)){
        if (comm->has_heredoc) {
            resolve_dum_heredoc(comm->here_doc_delimiter, 0);
            free_double_char(comm->here_doc_delimiter);
            comm->has_heredoc = 0;
        }
        comm->has_program = false;
        printf("minishell: %s: %s\n", comm->error, strerror(errno));
        return (0);
    }
	has_input(command, comm, last_heredoc_i, 0);
	has_output(command, comm);
	return (0);
}
