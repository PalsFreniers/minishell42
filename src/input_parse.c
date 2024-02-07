#include "minishell.h"

int	check_for_empty(char *buffer, int i)
{
	i++;
	while (buffer[i])
	{
		if (buffer[i] == '|')
		{
			printf("parse error near `|'\n");
			return (-1);
		}
		if (buffer[i] > 32 && buffer[i] < 127)
			return (0);
		i++;
	}
	printf("parse error near `|'\n");
	return (-1);
}

int	get_command_number(char *buffer)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	if (ft_strlen(buffer) == 0)
		return (0);
	while (buffer[i])
	{
		if (buffer[i] == '|')
		{
			if (check_for_empty(buffer, i) == -1)
				return (-1);
			increment_c_and_i(&c, &i);
		}
		else if (buffer[i] == '\"')
		{
			if (find_next_quote(buffer, &i, '\"') == -1)
				return (-1);
		}
		else if (buffer[i] == '\'')
		{
			if (find_next_quote(buffer, &i, '\'') == -1)
				return (-1);
		}
		else if (char_is_alphanum(buffer[i]) == 1)
		{
			while (buffer[i] && char_is_alphanum(buffer[i]) == 1)
				i++;
		}
	}
	return (c + 1);
}

char	**scrap_input(int command_number, char *usr_input)
{
	int	i;
	int	n;
	int	input_length;
	char **commands;

	input_length = 1;
	commands = malloc((command_number + 1) * sizeof(char *));
	commands[command_number] = NULL;
	if (!commands)
		return (NULL);
	n = 0;
	i = 0;
	while (input_length && n < command_number)
	{
		input_length = get_input_length(usr_input, i);
		if (input_length)
		{
			commands[n] = ft_strdupi(usr_input, &i, input_length);
			if (!commands[n])
				return (NULL);
			n++;
		}
	}
	return (commands);
}

int	get_input_length(char *buffer, int start_index)
{
	int	c;

	c = 0;
	if (buffer[start_index] == '|')
		++start_index;
	while (buffer[start_index] && buffer[start_index] != '|')
	{
		if (buffer[start_index] == '|')
			return (c);
		else if (buffer[start_index] == '\"')
		{
			increment_c_and_i(&c, &start_index);
			while (buffer[start_index] && buffer[start_index] != '\"')
				increment_c_and_i(&c, &start_index);
			if (buffer[start_index] == '\"')
				increment_c_and_i(&c, &start_index);
		}
		else if (buffer[start_index] == '\'')
		{
			increment_c_and_i(&c, &start_index);
			while (buffer[start_index] != '\'')
				increment_c_and_i(&c, &start_index);
			if (buffer[start_index] == '\'')
				increment_c_and_i(&c, &start_index);
		}
		else
			increment_c_and_i(&c, &start_index);
	}
	return (c);
}

