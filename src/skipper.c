/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_treat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 11:10:08 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_the_word(char *s, int *i)
{
	while (s[*i] && !(is_whitespace(s[*i])))
	{
		if (is_quote(s[*i]))
			find_next_quote(s, i, s[*i], 1);
		else if (is_parasit(s[*i]))
			return ;
		else
		{
			while (is_alphanum(s[*i]))
				*i = *i + 1;
		}
		return (skip_the_word(s, i));
	}
}

void	skip_to_the_next_word(char *s, int *i)
{
	while (s[*i] && (is_whitespace(s[*i])))
		*i = *i + 1;
}

void	skip_the_next_word(char *s, int *i)
{
	skip_to_the_next_word(s, i);
	skip_the_word(s, i);
}
