/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_treat_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/20 01:21:27 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

bool	first_character_env_invalid(char c)
{
	if (c >= 'a' && c <= 'z')
		return (0);
	if (c >= 'A' && c <= 'Z')
		return (0);
	if (c == '_')
		return (0);
	return (1);
}

bool	is_parasit(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

bool	bis_quote(char *s, int i)
{
	if (s[i] == '\'' || s[i] == '\"')
	{
		if (i > 0)
			if (s[i - 1] == '\\')
				return (0);
		return (1);
	}
	return (0);
}

bool	is_delimiter(char c)
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
