#include "minishell.h"

void	increment_c_and_i(int *counter, int *index)
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