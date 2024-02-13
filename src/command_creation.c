/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/13 11:17:40 by tdelage          ###   ########.fr       */
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

int	manage_shit(char *command, int i)
{
	int c;
	char ch;

	c = 0;
	ch = 'a';
	while (char_is_parasit(command[i]))
		i++;
	skip_to_the_next_word(command, &i);
	if (char_is_parasit(command[i]))
		ch = command[i];
	while (command[i] == ch)
		increment_both(&i, &c);
	if (ch == '<' && c >= 3)
		c = 3;
	else if (c >= 2)
		c = 2;
	if (!command[i] && c == 0)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	printf("syntax error near unexpected token `");
	while (c > 0)
	{
		c = c - 1;
		printf("%c", ch);
	}
	printf("\'\n");
	return (0);
}

int	parasit_only_treat(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i])
	{
		if (char_is_parasit(buffer[i]))
		{
			manage_shit(buffer, i);
			return (-1);
		}
		++i;
	}
	return (0);
}

int	is_first_command_valid(char *buffer)
{
	int j;
	bool empty;
	bool	parasit;

	j = 0;
	empty = true;
	parasit = false;
	skip_to_the_next_word(buffer, &j);
	if (!buffer[j])
		return (0);
	while (buffer[j] && buffer[j] != '|')
	{
		if (!char_is_parasit(buffer[j]) && !char_is_whitespace(buffer[j]))
			empty = false;
		else if (char_is_parasit(buffer[j]))
			parasit = true;
		++j;
	}
	if (empty)
	{
		if (parasit && !buffer[j])
			return (parasit_only_treat(buffer));
		printf("syntax error near unexpected token `|'\n");
		return (-1);
	}
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
	if (is_first_command_valid(buffer))
		return (-1);
	while (buffer[i])
	{
		if (cross_and_count(buffer, &c, &i))
			return (-1);
	}
	return (c + 1);
}

int	create_the_com_table(char *usr_input, char **commands, int command_number)
{
	int	i;
	int	n;
	int	command_length;

	command_length = 1;
	i = 0;
	n = 0;
	while (n < command_number)
	{
		if (i != 0 && usr_input[i] == '|')
			++i;
		while (char_is_whitespace(usr_input[i]))
			++i;
		command_length = get_command_length(usr_input, i);
		commands[n] = ft_strdupi(usr_input, &i, command_length);
		if (!commands[n])
			return (1);
		n++;
		if (usr_input[i] == '|')
			++i;
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
