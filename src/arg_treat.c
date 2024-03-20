/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_treat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/20 01:21:01 by dosokin          ###   ########.fr       */
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
		if (is_whitespace(ch) || is_parasit(ch) || bis_quote(command, i))
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
		else
			i++;
	}
	return (c);
}

static int	get_the_next_arg_length(char *command, int j, bool *has_program)
{
	int	length;

	length = 0;
	if (bis_quote(command, j))
		return (get_the_next_arg_length_quote_case(command, &j));
	while (command[j] && !(is_whitespace(command[j]))
		&& !(is_parasit(command[j])))
	{
		if (command[j] == '\\')
			++j;
		else if (bis_quote(command, j))
			return (length + get_the_next_arg_length(command, j, NULL));
		else
			increment_both(&j, &length);
	}
	if (has_program && length == 0)
		*has_program = false;
	return (length);
}

int	get_the_next_arg_length_quote_case(char *command, int *j)
{
	int	tempo;
	int	length;

	tempo = *j;
	find_next_coat(command, j, command[*j], &tempo);
	length = *j - tempo - 2;
	if (!is_whitespace(command[*j]))
		return (length + get_the_next_arg_length(command, *j, NULL));
	return (length);
}

char	*get_the_next_arg(char *command, int *i, bool *has_program)
{
	t_data_gtna	data;

	data = init_gtna();
	skip_in_outs_hds(command, i);
	data.length = get_the_next_arg_length(command, *i, has_program);
	data.argument = malloc((data.length + 1) * sizeof(char));
	if (!data.argument)
		return (NULL);
	while (command[*i] && data.j < data.length)
		get_the_next_arg_child(command, i, &data);
	data.argument[data.j] = '\0';
	skip_ending_quotes(command, i, data.length);
	return (data.argument);
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
