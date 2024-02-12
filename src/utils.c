#include "minishell.h"

void	increment_both(int *counter, int *index)
{
	*counter = *counter + 1;
	*index = *index + 1;
}

void	free_all(char **commands)
{
	int	i;

	i = 0;
	if (commands)
	{
		while (commands[i])
		{
			free(commands[i]);
			i++;
		}
		free(commands);
	}
}

char *entry_to_text(t_entry entry)
{
	static char *table[] = {
		"ENTRY_HEREDOC",
		"ENTRY_INPUT",
		"ENTRY_PIPE",
		"NO_ENTRY",
	};
	return(table[entry]);
}

char *exit_to_text(t_exit exit)
{
	static char *table[] = {
		"EXIT_OUTPUT",
		"EXIT_PIPE",
		"EXIT_STDOUT",
	};
	return(table[exit]);
}