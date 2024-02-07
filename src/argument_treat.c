#include "minishell.h"

int	get_argc(char *command, int *i)
{
	int	j;
	int	c;

	c = 0;
	j = *i;
	while (command[j] && char_is_whitespace(command[j]) == 1)
		++j;
	while (command[j])
	{
		if (command[j] == '<' || command[j] == '>')
		{
			while (char_is_parasit(command[j]) == 1)
				++j;
			j = skip_to_the_next_word(command, j);
			j = skip_the_word(command, j);
		}
		else if (char_is_alphanum(command[j]) == 1
			&& (char_is_whitespace(command[j]) == -1))
		{
			++c;
			while (command[j] && char_is_whitespace(command[j]) == -1
				&& char_is_quote(command[j]) == -1)
				++j;
		}
		else if (char_is_quote(command[j]) == 1)
		{
			if (command[j] == '\'')
				find_next_quote(command, &j, '\'');
			else
				find_next_quote(command, &j, '\"');
			++c;
		}
		else
			++j;
	}
	return (c + 1);
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
	while (command[j] && (char_is_whitespace(command[j]) == -1))
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

	while (command[*i] && (char_is_whitespace(command[*i]) == 1))
		*i = *i + 1;
	length = get_the_next_arg_length(command, i);
	argument = malloc((length + 1) * sizeof(char));
	j = 0;
	while (j < length)
	{
		if (command[*i] == '\"')
			*i = *i + 1;
		else
		{
			argument[j] = command[*i];
			*i = *i + 1;
			j++;
		}
	}
	argument[j] = 0;
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
	c = get_argc(command, i);
	if (c)
	{
		arguments = malloc((c + 2) * sizeof(char *));
		arguments[j] = ft_strdup(program_name);
		j++;
		while (j < c)
		{
			while (command[*i] && char_is_whitespace(command[*i]) == 1)
				*i = *i + 1;
			if (command[*i] == '<' || command[*i] == '>')
			{
				while (char_is_parasit(command[*i]) == 1)
					*i = *i + 1;
				*i = skip_to_the_next_word(command, *i);
				*i = skip_the_word(command, *i);
			}
			arguments[j] = get_the_next_arg(command, i);
			++j;
		}
		arguments[j] = NULL;
	}
	return (arguments);
}
