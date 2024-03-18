/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:53:37 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/05 12:24:04 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	manage_shit(char *command, int i, char ch)
{
	int	c;

	c = 0;
	++i;
	while (command[i] && is_whitespace(command[i]))
		++i;
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
	while (c-- > 0)
		printf("%c", ch);
	printf("\'\n");
	return (0);
}

static int	parasit_only_treat(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (bis_quote(buffer, i))
			find_next_quote(buffer, &i, buffer[i], 1);
		else if (is_parasit(buffer[i]))
		{
			if (is_parasit(buffer[i + 1]) && buffer[i] == buffer[i + 1])
				++i;
			if (check_next_char_errority(buffer, i))
				return (0);
			++i;
		}
		else
			++i;
	}
	return (1);
}

int	first_command_valid(char *buffer)
{
	int		j;
	bool	empty;
	bool	parasit;

	j = 0;
	empty = true;
	parasit = false;
	skip_to_the_next_word(buffer, &j);
	if (!buffer[j])
		return (0);
	while (buffer[j] && buffer[j] != '|')
		if (!check_character(buffer, &j, &empty, &parasit))
			return (0);
	if (empty)
	{
		if (parasit)
			return (parasit_only_treat(buffer));
		printf("syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

int	check_usr_input_for_errors(char *input)
{
	int	i;

	i = 0;
	if (!first_command_valid(input))
		return (1);
	while (input[i])
	{
		if (bis_quote(input, i))
		{
			if (find_next_quote(input, &i, input[i], 2) == -1)
				return (1);
		}
		else if (is_parasit(input[i]))
		{
			if (is_parasit(input[i + 1]) && input[i] == input[i + 1])
				++i;
			if (check_next_char_errority(input, i))
				return (1);
			++i;
		}
		else
			++i;
	}
	return (0);
}
