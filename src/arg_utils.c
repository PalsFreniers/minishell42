/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/08 10:03:54 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_in_outs_hds(char *command, int *i)
{
	skip_to_the_next_word(command, i);
	while (is_parasit(command[*i]))
	{
		while (is_parasit(command[*i]))
			*i = *i + 1;
		skip_the_next_word(command, i);
		skip_to_the_next_word(command, i);
	}
}

void	skip_ending_quotes(char *command, int *i, int length)
{
	(void)length;
	if (bis_quote(command, *i))
	{
		while (bis_quote(command, *i))
			*i = *i + 1;
	}
}

int	gtna_quote_case(char *command, int *i, char *type_quote)
{
	if (*type_quote != 'a' && command[*i] == *type_quote)
	{
		*type_quote = 'a';
		*i = *i + 1;
		return (1);
	}
	else if (*type_quote == 'a')
	{
		*type_quote = command[*i];
		*i = *i + 1;
		return (1);
	}
	return (0);
}
