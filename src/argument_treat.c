#include "minishell.h"

int	get_argc(char *command, int i)
{
	int	c;
	int reset;

	reset = 1;
	c = 0;
	while (command[i])
	{
		if (char_is_whitespace(command[i]) == 1)
		{
			reset = 1;
			while (command[i] && char_is_whitespace(command[i]) == 1)
				++i;
		}
		else if (char_is_parasit(command[i]) == 1)
		{
			while (char_is_parasit(command[i]) == 1)
				++i;
			skip_the_next_word(command, &i);
		}
		else if (char_is_quote(command[i]) == 1)
		{
			if (reset == 1)
			{
				c++;
				reset = 0;
			}
			find_next_quote(command, &i, command[i]);
		}
		else if (char_is_alphanum(command[i]) == 1)
		{
			if (reset == 1)
			{
				c++;
				reset = 0;
			}
			while (char_is_alphanum(command[i]) == 1)
				++i;
		}
	}
	return (c);
}

int	get_the_next_arg_length(char *command, int *i)
{
	int	length;
	int j;
	int tempo;

	j = *i;
	length = 0;
	if (char_is_quote(command[j]) == 1)
	{
		tempo = j;
		find_next_quote(command, &j, command[j]);
		length = length + (j - tempo - 2);
		if (char_is_whitespace(command[j] == -1))
			return (length + get_the_next_arg_length(command, &j));
		return (length);
	}
	while (command[j] && (char_is_whitespace(command[j]) == -1) && (char_is_parasit(command[j]) == -1))
	{
		if (char_is_quote(command[j]) == 1)
			return (length + get_the_next_arg_length(command, &j));
		++length;
		++j;
	}
	return (length);
}

char	*get_the_next_arg(char *command, int *i)
{
	char	*argument;
	int		length;
	int		j;

	length = get_the_next_arg_length(command, i);
	argument = malloc((length + 1) * sizeof(char));
	j = 0;
	while (j < length)
	{
		if (char_is_quote(command[*i]) == 1)
			*i = *i + 1;
		else
		{
			argument[j] = command[*i];
			*i = *i + 1;
			j++;
		}
	}
	argument[j] = '\0';
	if (char_is_quote(command[*i]) == 1)
		*i = *i + 1;
	return (argument);
}

char	**get_the_arguments(char *command, int *i, char *program_name)
{
	int		c;
	int		j;
	char	**arguments;

	arguments = NULL;
	j = 0;
	c = get_argc(command, *i);
	arguments = malloc((c + 2) * sizeof(char *));
	arguments[j] = ft_strdup(program_name);
	j++;
	while (j < c + 1)
	{
		if (char_is_whitespace(command[*i]) == 1)
			while (command[*i] && char_is_whitespace(command[*i]) == 1)
				*i = *i + 1;
		else if (char_is_parasit(command[*i]) == 1)
		{
			while (command[*i] && char_is_parasit(command[*i]) == 1)
				*i = *i + 1;
			skip_the_next_word(command, i);
		}
		else
		{
			arguments[j] = get_the_next_arg(command, i);
			++j;
		}
	}
	arguments[j] = NULL;
	return (arguments);
}
