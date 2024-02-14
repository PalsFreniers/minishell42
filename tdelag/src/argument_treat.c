/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_treat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 11:06:32 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_argc(char *command, int i)
{
	int		c;
	int		reset;
	char	ch;

	reset = 1;
	c = 0;
	while (command[i] && i < (int)ft_strlen(command))
	{
		ch = command[i];
		if (char_is_whitespace(ch) || char_is_parasit(ch) || char_is_quote(ch))
			skip_undesired(command, &i, &reset, &c);
		else if (char_is_alphanum(ch))
		{
			if (reset == 1)
			{
				c++;
				reset = 0;
			}
			while (char_is_alphanum(command[i]))
				++i;
		}
	}
	return (c);
}

int	get_the_next_arg_length(char *command, int j)
{
	int	length;
	int	tempo;

	length = 0;
	if (char_is_quote(command[j]))
	{
		tempo = j;
		find_next_quote(command, &j, command[j], 1);
		length = length + (j - tempo - 2);
		if (!char_is_whitespace(command[j]))
			return (length + get_the_next_arg_length(command, j));
		return (length);
	}
	while (command[j] && !(char_is_whitespace(command[j]))
		&& !(char_is_parasit(command[j])))
	{
		if (char_is_quote(command[j]))
			return (length + get_the_next_arg_length(command, j));
		++length;
		++j;
	}
	return (length);
}

int	gtna_quote_case(char *command, int *i, char *type_quote)
{
	if (*type_quote != 'a' && command[*i] == *type_quote)
	{
		*type_quote = 'a';
		*i = *i + 1;
		return (1);
	}
	else if (*type_quote == 'a')
	{
		*type_quote = command[*i];
		*i = *i + 1;
		return (1);
	}
	return (0);
}

char	*get_the_next_arg(char *command, int *i)
{
	char	*argument;
	int		length;
	char	type_quote;
	int		j;

	type_quote = 'a';
	skip_to_the_next_word(command, i);
	while (char_is_parasit(command[*i]))
	{
		while (char_is_parasit(command[*i]))
			*i = *i + 1;
		skip_the_next_word(command, i);
		skip_to_the_next_word(command, i);
	}
	length = get_the_next_arg_length(command, *i);
	argument = malloc((length + 1) * sizeof(char));
	j = 0;
	while (j < length)
	{
		if (char_is_quote(command[*i]))
		{
			if (!(gtna_quote_case(command, i, &type_quote)))
				dup_and_get_next(&command, i, &argument, &j);
		}
		else
			dup_and_get_next(&command, i, &argument, &j);
	}
	argument[j] = '\0';
	if (char_is_quote(command[*i]))
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
	arguments[j++] = ft_strdup(program_name);
	while (j < c + 1)
	{
		if (char_is_whitespace(command[*i]))
			*i = *i + 1;
		else if (char_is_parasit(command[*i]))
		{
			while (command[*i] && char_is_parasit(command[*i]))
				*i = *i + 1;
			skip_the_next_word(command, i);
		}
		else
			arguments[j++] = get_the_next_arg(command, i);
	}
	arguments[j] = NULL;
	return (arguments);
}
