/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/20 01:32:34 by dosokin          ###   ########.fr       */
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

int	get_an_argument(char *command, int *i, char **arguments, int *j)
{
	if (is_whitespace(command[*i]))
		*i = *i + 1;
	else if (is_parasit(command[*i]))
	{
		while (command[*i] && is_parasit(command[*i]))
			*i = *i + 1;
		skip_the_next_word(command, i);
	}
	else
	{
		arguments[*j] = get_the_next_arg(command, i, NULL);
		while (bis_quote(command, *i))
			*i = *i + 1;
		if (!arguments[*j])
			return (1);
		*j = *j + 1;
	}
	return (0);
}

void	get_the_next_arg_child(char *command, int *i, t_data_gtna *data)
{
	if (command[*i] == '\\' && (is_quote_o_pipe(command[*i + 1])))
	{
		*i = *i + 1;
		dup_and_get_next(&command, i, &data->argument, &data->j);
	}
	else if (bis_quote(command, *i))
	{
		if (!(gtna_quote_case(command, i, &data->type_quote)))
			dup_and_get_next(&command, i, &data->argument, &data->j);
	}
	else
		dup_and_get_next(&command, i, &data->argument, &data->j);
}
