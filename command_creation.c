/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 11:09:30 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cross_and_count(char *buffer, int *c, int *i)
{
	if (buffer[*i] == '|')
	{
		if (check_for_empty(buffer, *i) == -1)
			return (-1);
		increment_both(c, i);
	}
	else if (char_is_quote(buffer[*i]))
	{
		if (find_next_quote(buffer, i, buffer[*i]) == -1)
			return (-1);
	}
	else if (char_is_alphanum(buffer[*i]))
	{
		while (buffer[*i] && char_is_alphanum(buffer[*i]))
			*i = *i + 1;
	}
	else
		*i = *i + 1;
	return (0);
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
		if (cross_and_count(buffer, &c, &i))
			return (-1);
	}
	return (c + 1);
}

int	create_the_com_table(char *usr_input, char ***commands, int command_number)
{
	int	i;
	int	n;
	int	command_length;

	command_length = 1;
	i = 0;
	n = 0;
	while (command_length && n < command_number)
	{
		if (usr_input[i] == '|')
			++i;
		while (char_is_whitespace(usr_input[i]))
			++i;
		command_length = get_command_length(usr_input, i);
		if (command_length)
		{
			(*commands)[n] = ft_strdupi(usr_input, &i, command_length);
			if (!(*commands)[n])
				return (1);
			n++;
		}
	}
	return (0);
}

int	get_command_length(char *buffer, int i)
{
	int	c;
	int	tempo;

	c = 0;
	while (buffer[i] && buffer[i] != '|')
	{
		if (char_is_quote(buffer[i]))
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
	return (c);
}
