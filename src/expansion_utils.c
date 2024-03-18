/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:49:53 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/06 18:00:20 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_quote_expansion(char *usr_input, int *i, int *l)
{
	int	j;

	j = *i;
	find_next_quote(usr_input, i, '\'', 1);
	*l = *l + (*i - j);
}

void	heredoc_detected_expansion(char *usr_input, int *i, int *l)
{
	int	j;

	j = *i;
	*i = *i + 2;
	skip_the_next_word(usr_input, i);
	*l = *l + (*i - j);
}

int	treat_dollar_case_exp(char *usr_input, int *i, int *l,
		bool *is_double_quote)
{
	if (usr_input[*i + 1] == '$')
	{
		*i = *i + 2;
		*l = *l + 2;
		return (0);
	}
	else if (bis_quote(usr_input, *i + 1) && !(*is_double_quote))
	{
		*i = *i + 1;
		return (0);
	}
	return (1);
}

int	treat_the_char_exp(char *usr_input, int *i, int *l, bool *is_double_quote)
{
	if (usr_input[*i] == '\'' && !(*is_double_quote))
		single_quote_expansion(usr_input, i, l);
	else if (usr_input[*i] == '\"')
	{
		*is_double_quote = !(*is_double_quote);
		increment_both(i, l);
	}
	else if (!(*is_double_quote) && (usr_input[*i] == '<' && usr_input[*i
				+ 1] == '<'))
		heredoc_detected_expansion(usr_input, i, l);
	else if (usr_input[*i] == '$')
		return (treat_dollar_case_exp(usr_input, i, l, is_double_quote));
	else
		increment_both(i, l);
	return (0);
}

int	get_length_expanded(char *usr_input, char **envp, int last)
{
	t_length_exp	data;

	data.l = 0;
	data.i = 0;
	data.is_double_quote = false;
	data.last = last;
	while (usr_input[data.i])
		if (treat_the_char_exp(usr_input, &data.i, &data.l,
				&data.is_double_quote))
			get_length_dollar(usr_input, envp, &data);
	return (data.l);
}
