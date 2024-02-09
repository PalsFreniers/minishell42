#include "minishell.h"

void	skip_the_word(char *s, int *i)
{
	while (s[*i] && !(char_is_whitespace(s[*i])))
	{
		if (char_is_quote(s[*i]))
			find_next_quote(s, i, s[*i]);
		else if (char_is_parasit(s[*i]))
			return ;
		else
		{
			while (char_is_alphanum(s[*i]))
				*i = *i + 1;
		}
		return (skip_the_word(s, i));
	}
}

void	skip_to_the_next_word(char *s, int *i)
{
	while (s[*i] && (char_is_whitespace(s[*i])))
		*i = *i + 1;
}	

void	skip_the_next_word(char *s, int *i)
{
	skip_to_the_next_word(s, i);
	skip_the_word(s, i);
}

int	is_prog_start(char *s, int i)
{
	if (char_is_quote(s[i]))
	{
		++i;
		while (s[i] && char_is_whitespace(s[i]))
			i++;
		if (!s[i])
			return (-1);
		return (is_prog_start(s, i));
	}
	if (char_is_parasit(s[i]))
		return (-1);
	return (1);
}

char	*get_the_prog_name(char *command, int *i)
{
	char	*name;
	int		length;
	int		j;

	length = get_the_next_arg_length(command, i);
	name = malloc((length + 1) * sizeof(char));
	j = 0;
	while (j < length)
	{
		if (char_is_quote(command[*i]))
			*i = *i + 1;
		else
		{
			name[j] = command[*i];
			*i = *i + 1;
			j++;
		}
	}
	if (char_is_quote(command[*i]))
		*i = *i + 1;
	name[j] = '\0';
	return (name);
}

char *get_the_program(char *command, int *i)
{
	while (command[*i])
	{
		while (command[*i] && char_is_whitespace(command[*i]))
			*i = *i + 1;
		if (char_is_parasit(command[*i]))
		{
			while (command[*i] && char_is_parasit(command[*i]))
				*i = *i + 1;
			skip_the_next_word(command, i);
		}
		else
			return (get_the_prog_name(command, i));
	}
	return (NULL);
}