/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/04 12:44:53 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_empty(char *buffer, int i)
{
	i++;
	while (buffer[i])
	{
		if (buffer[i] == '|')
		{
			printf("parse error near `|'\n");
			return (-1);
		}
		if (!is_parasit(buffer[i]) && !is_whitespace(buffer[i]))
			return (0);
		i++;
	}
	printf("parse error near `|'\n");
	return (-1);
}

char	**scrap_input(int command_number, char *usr_input)
{
	char	**commands;

	commands = malloc((command_number + 1) * sizeof(char *));
	if (!commands)
		return (NULL);
	commands[command_number] = NULL;
	if (create_the_com_table(usr_input, commands, command_number))
		return (NULL);
	return (commands);
}
