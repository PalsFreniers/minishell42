#include "minishell.h"

int	check_for_empty(char *buffer, int i)
{
	i++;
	while (buffer[i])
	{
		if (buffer[i] == '|')
		{
			//printf("parse error near `|'\n");
			return (-1);
		}
		if (buffer[i] > 32 && buffer[i] < 127)
			return (0);
		i++;
	}
	//printf("parse error near `|'\n");
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
		else if (char_is_quote(buffer[i]) == 1)
		{
			if (find_next_quote(buffer, &i, buffer[i]) == -1)
				return (-1);
		}
		else if (char_is_alphanum(buffer[i]) == 1)
		{
			while (buffer[i] && char_is_alphanum(buffer[i]) == 1)
				i++;
		}
		else
			i++;
	}
	return (c + 1);
}

char	**scrap_input(int command_number, char *usr_input)
{
	int	i;
	int	n;
	int	command_length;
	char **commands;

	command_length = 1;
	commands = malloc((command_number + 1) * sizeof(char *));
	commands[command_number] = NULL;
	if (!commands)
		return (NULL);
	n = 0;
	i = 0;
	while (command_length && n < command_number)
	{
		if (usr_input[i] == '|')
			++i;
		while (char_is_whitespace(usr_input[i]) == 1)
			i++;
		command_length = get_command_length(usr_input, i);
		if (command_length)
		{
			commands[n] = ft_strdupi(usr_input, &i, command_length);
			if (!commands[n])
				return (NULL);
			n++;
		}
	}
	return (commands);
}

int	get_command_length(char *buffer, int i)
{
	int	c;
	int tempo;

	c = 0;
	while (buffer[i] && buffer[i] != '|')
	{
		if (char_is_quote(buffer[i]) == 1)
		{
			tempo = i;
			find_next_quote(buffer, &i, buffer[i]);
			c += i - tempo;
		}
		else
		{
			i++;
			c++;
		}
	}
	//printf("command length: %d\n", c);
	return (c);
}

