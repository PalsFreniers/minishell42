#include "minishell.h"

int	get_the_next_hd_length(char *command, int i)
{
	int	length;

	length = i;
	if (char_is_quote(command[length]) == 1)
	{
		++length;
		if (command[length - 1] == '\'')
		{
			while (command[length] != '\'')
				++length;
		}
		else if (command[length - 1] == '\"')
		{
			while (command[length] != '\"')
				++length;
		}
		return (length + 1 - i);
	}
	while (command[length] && (char_is_whitespace(command[length]) == -1))
    {
        if (command[length] == '<' && command[length + 1] == '<')
            return (length - i);
		++length;
    }
	return (length - i);
}

char	*get_the_next_heredoc(char *command, int *i)
{
	char	*argument;
	int		length;
	int		j;

	while (command[*i] && (char_is_whitespace(command[*i]) == 1))
		*i = *i + 1;
	length = get_the_next_hd_length(command, *i);
	argument = malloc((length + 1) * sizeof(char));
	j = 0;
	while (j < length)
	{
		argument[j] = command[*i];
		*i = *i + 1;
		j++;
	}
	argument[j] = 0;
	return (argument);
}

void    here_doc_init(t_com *comm, char *command, int i)
{
    int j;

    j = 0;
    comm->here_doc_delimiter = malloc((comm->is_heredoc + 1) * sizeof(char*));
    while (command[i])
    {
        if (char_is_quote(command[i]) == 1)
            find_next_quote(command, &i, command[i]);
        if (command[i] == '<' && command[i + 1] == '<')
        {
            i += 2;
            //comm->here_doc_delimiter[j] = get_the_next_heredoc(command, &i);
            skip_to_the_next_word(command, &i);
            comm->here_doc_delimiter[j] = get_the_next_arg(command, &i);
            ++j;
        }
        else
            ++i;
    }
    comm->here_doc_delimiter[j] = NULL;
}

void    is_heredoc(char *command, t_com *comm, int *i)
{
    comm->is_heredoc = 0;
    comm->here_doc_delimiter = NULL;
    while (command[*i])
    {
        if (char_is_quote(command[*i]) == 1)
            find_next_quote(command, i, command[*i]);
        else if (command[*i] == '<' && command[*i + 1] == '<')
        {       
            comm->is_heredoc++;
            *i = *i + 2;
        }
        else
            *i = *i + 1;
    }
    if (comm->is_heredoc)
        here_doc_init(comm, command, 0);
}
