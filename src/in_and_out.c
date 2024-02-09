#include "minishell.h"

void    is_input(char *command, t_com *comm, int last_index_hd)
{
    int i;

    i = 0;
    comm->is_input = false;
    comm->input = NULL;
    while (command[i])
    {
        if (char_is_quote(command[i]))
            find_next_quote(command, &i, command[i]);
        else if (command[i] == '<')
        {
            if (command[i + 1] == '<')
            {
                while (command[i] == '<')
                    ++i;
                skip_the_next_word(command, &i);
            }
            else
            {
                i = i + 1;
                if (comm->is_input)
                {
                    close(comm->fd_input);
                    free(comm->input);
                }
                comm->is_input = true;
                if (i > last_index_hd)
                    comm->entry = ENTRY_INPUT;
                comm->input = get_the_next_arg(command, &i);
                comm->fd_input = open(comm->input, O_RDONLY);
                if (comm->fd_input < 0 && !comm->error)
                    comm->error = ft_strdup((const char*)comm->input);
            }
        }
        else
            i = i + 1;
    }
}

void    is_output(char *command, t_com *comm)
{
    int i;

    i = 0;

    comm->is_output = false;
    comm->output = NULL;
    while (command[i])
    {
        if (char_is_quote(command[i]))
            find_next_quote(command, &i, command[i]);
        else if (command[i] == '>')
        {
            if (comm->is_output)
            {
                close(comm->fd_output);
                free(comm->output);
            }
            comm->is_output = true;
            if (command[i + 1] == '>')
            {
                i += 2;
                comm->outkind = APPEND;
                comm->output = get_the_next_arg(command, &i);
                comm->fd_output = open(comm->output, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            }
            else
            {
                ++i;
                comm->outkind = OVERWRITE;
                comm->output = get_the_next_arg(command, &i);
                comm->fd_output = open(comm->output, O_CREAT | O_WRONLY,  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            }
        }
        else
            i = i + 1;
    }
}
