/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_treat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 11:08:41 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alphanum(char c)
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

int	is_whitespace(char c)
{
	if (c == '\r' || c == ' ' || c == '\t')
		return (1);
	if (c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	find_next_quote(char *buffer, int *i, char quote_type, int x)
{
	*i = *i + 1;
	while (buffer[*i] && buffer[*i] != quote_type)
		*i = *i + 1;
	if (!buffer[*i] && x == 2)
	{
		printf("unclosed quotes\n");
		return (-1);
	}
	*i = *i + 1;
	return (1);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_delimiter(char c)
{
	if (c == '_')
		return (0);
	if (c >= '0' && c <= '9')
		return (0);
	if (c >= 'a' && c <= 'z')
		return (0);
	if (c >= 'A' && c <= 'Z')
		return (0);
	return (1);
}
