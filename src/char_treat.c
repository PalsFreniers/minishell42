/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_treat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/20 01:20:24 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_alphanum(char c)
{
	if (c == '|')
		return (0);
	else if (c == '\'' || c == '\"')
		return (0);
	else if (c == '<' || c == '>')
		return (0);
	else if (is_whitespace(c))
		return (0);
	else if (c >= 32 && c < 127)
		return (1);
	else
		return (0);
}

int	find_next_quote(char *buffer, int *i, char quote_type, int x)
{
	*i = *i + 1;
	while (buffer[*i] && (buffer[*i] != quote_type || !bis_quote(buffer, *i)))
		*i = *i + 1;
	if (!buffer[*i])
	{
		if (x == 2)
			printf("unclosed quotes\n");
		return (-1);
	}
	*i = *i + 1;
	return (1);
}

int	find_next_coat(char *buffer, int *i, char quote_type, int *x)
{
	*i = *i + 1;
	while (buffer[*i] && (buffer[*i] != quote_type || !bis_quote(buffer, *i)))
	{
		if (buffer[*i] == '\\' && (is_quote(buffer[*i + 1]) || buffer[*i
					+ 1] == '|'))
			*x = *x + 1;
		*i = *i + 1;
	}
	*i = *i + 1;
	return (1);
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

bool	is_quote_o_pipe(char c)
{
	if (is_quote(c))
		return (1);
	if (c == '|')
		return (1);
	return (0);
}
