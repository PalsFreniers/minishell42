/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_treat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 11:47:26 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_error_output(char *command, int i)
{
	skip_to_the_next_word(command, &i);
	if (!command[i])
		return (1);
	if (char_is_delimiter(command[i]))
		return (1);
	return (0);
}

char	check_for_next_char(char *command, int i)
{
	++i;
	while (command[i] && char_is_whitespace(command[i]))
		++i;
	return (command[i]);
}
