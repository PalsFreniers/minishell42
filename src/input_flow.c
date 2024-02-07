#include "minishell.h"

void    is_input(char *command, t_com *comm, int *i)
{
    comm->is_input = false;
    comm->input = NULL;
    while (command[*i])
    {
        if (char_is_quote(command[*i]) == 1)
            find_next_quote(command, i, command[*i]);
        if (command[*i] == '<' && command[*i + 1] != '<')
        {
            if (comm->is_input)
                free(comm->input);
            comm->is_input = true;
            *i = *i + 1;
            comm->input = get_the_next_arg(command, i);
        }
        else
            *i = *i + 1;
    }
}