/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:53:37 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 18:16:14 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_character(char *buffer, int *j, bool *empty, bool *parasit)
{
	if (is_quote(buffer[*j]))
	{
		*empty = false;
		if (find_next_quote(buffer, j, buffer[*j], 2) == -1)
			return (0);
	}
	else
	{
		if (!is_parasit(buffer[*j]) && !is_whitespace(buffer[*j]))
			*empty = false;
		else if (is_parasit(buffer[*j]))
			*parasit = true;
		*j = *j + 1;
	}
	return (1);
}

int	check_next_char_errority(char *input, int i)
{
	char	ch;

	ch = check_for_next_char(input, i);
	if (!ch)
	{
		error_exit_hd(input, i);
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (ch == '|')
	{
		error_exit_hd(input, i);
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	if (is_parasit(ch))
	{
		error_exit_hd(input, i);
		manage_shit(input, i, ch);
		return (1);
	}
	return (0);
}

int	is_usr_input_blank(char *usr_input)
{
	int	i;

	i = 0;
	skip_to_the_next_word(usr_input, &i);
	if (!usr_input[i])
		return (1);
	return (0);
}
