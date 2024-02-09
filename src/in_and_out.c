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
                    free(comm->input);
                comm->is_input = true;
                if (i > last_index_hd)
                    comm->entry = ENTRY_INPUT;
                comm->input = get_the_next_arg(command, &i);
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
                free(comm->output);
            comm->is_output = true;
            if (command[i + 1] == '>')
            {
                i += 2;
                comm->outkind = APPEND;
                comm->output = get_the_next_arg(command, &i);
            }
            else
            {
                ++i;
                comm->outkind = OVERWRITE;
                comm->output = get_the_next_arg(command, &i);
            }
        }
        else
            i = i + 1;
    }
}
