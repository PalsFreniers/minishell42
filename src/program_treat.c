#include "minishell.h"

int	skip_the_word(char *s, int i)
{
	if (s[i] == '-')
		i++;
	while (s[i] && char_is_whitespace(s[i]) == 1)
		++i;
	while (s[i] && char_is_whitespace(s[i]) == -1)
	{
		if (char_is_quote(s[i]) == 1)
		{
			if (s[i] == '\'')
			{
				if (find_next_quote(s, &i, '\'') == -1)
					return (-1);
			}
			else
			{
				if (find_next_quote(s, &i, '\"') == -1)
					return (-1);
			}
		}
		else
			i++;
	}
	if (!s[i])
		return (-1);
	return (i);
}

int	skip_to_the_next_word(char *s, int i)
{
	while (s[i] && (char_is_whitespace(s[i]) == 1))
		++i;
	if (!s[i])
		return (-1);
	return (i);
}	

int	is_prog_start(char *s, int i)
{
	if (char_is_quote(s[i]) == 1)
	{
		++i;
		while (s[i] && char_is_whitespace(s[i]) == 1)
			i++;
		if (!s[i])
			return (-1);
		return (is_prog_start(s, i));
	}
	if (s[i] == '-')
		return (-1);
	if (s[i] == '<' || s[i] == '>')
		return (-1);
	return (1);
}

int	char_is_parasit(char c)
{
	if (c == '-')
		return (1);
	if (c == '<' || c == '>')
		return (1);
	return (-1);
}

char *get_the_program(char *command, int *i)
{
	while (command[*i])
	{
		if (is_prog_start(command, *i) == 1)
			return(get_the_next_arg(command, i));
		while (char_is_parasit(command[*i]) == 1)
			*i = *i + 1;
		if (*i == -1)
			return (NULL);
		*i = skip_to_the_next_word(command, *i);
		if (*i == -1)
			return (NULL);
		if (is_prog_start(command, *i) == 0)
			return(get_the_next_arg(command, i));
		while (char_is_parasit(command[*i]) == 1)
			*i = *i + 1;
		if (*i == -1)
			return (NULL);
		*i = skip_the_word(command, *i);
		if (*i == -1)
			return (NULL);
	}
	return (NULL);
}