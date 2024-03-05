/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_treat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/05 12:07:13 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_argc(char *command, int i)
{
	int		c;
	int		reset;
	char	ch;

	reset = 1;
	c = 0;
	while (command[i])
	{
		ch = command[i];
		if (is_whitespace(ch) || is_parasit(ch) || is_quote(ch))
			skip_undesired(command, &i, &reset, &c);
		else if (is_alphanum(ch))
		{
			if (reset == 1)
			{
				c++;
				reset = 0;
			}
			while (is_alphanum(command[i]))
				++i;
		}
	}
	return (c);
}

static int	get_the_next_arg_length(char *command, int j, bool *has_program)
{
	int	length;
	int	tempo;

	length = 0;
	if (is_quote(command[j]))
	{
		tempo = j;
		find_next_quote(command, &j, command[j], 1);
		length = length + (j - tempo - 2);
		if (!is_whitespace(command[j]))
			return (length + get_the_next_arg_length(command, j, NULL));
		return (length);
	}
	while (command[j] && !(is_whitespace(command[j]))
		&& !(is_parasit(command[j])))
	{
		if (is_quote(command[j]))
			return (length + get_the_next_arg_length(command, j, NULL));
		++length;
		++j;
	}
	if (has_program && length == 0)
		*has_program = false;
	return (length);
}

char	*get_the_next_arg(char *command, int *i, bool *has_program)
{
	char	*argument;
	int		length;
	char	type_quote;
	int		j;

	type_quote = 'a';
	skip_in_outs_hds(command, i);
	length = get_the_next_arg_length(command, *i, has_program);
	argument = malloc((length + 1) * sizeof(char));
	if (!argument)
		return (NULL);
	j = 0;
	while (j < length)
	{
		if (is_quote(command[*i]))
		{
			if (!(gtna_quote_case(command, i, &type_quote)))
				dup_and_get_next(&command, i, &argument, &j);
		}
		else
			dup_and_get_next(&command, i, &argument, &j);
	}
	argument[j] = '\0';
	skip_ending_quotes(command, i, length);
	return (argument);
}

int	get_an_argument(char *command, int *i, char **arguments, int *j)
{
	if (is_whitespace(command[*i]))
		*i = *i + 1;
	else if (is_parasit(command[*i]))
	{
		while (command[*i] && is_parasit(command[*i]))
			*i = *i + 1;
		skip_the_next_word(command, i);
	}
	else
	{
		arguments[*j] = get_the_next_arg(command, i, NULL);
		if (!arguments[*j])
			return (1);
		*j = *j + 1;
	}
	return (0);
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
	if (!arguments)
		return (NULL);
	arguments[j++] = ft_strdup(program_name);
	while (j < c + 1)
	{
		if (get_an_argument(command, i, arguments, &j))
			return (arguments);
	}
	arguments[j] = NULL;
	return (arguments);
}
