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

int	manage_errored_output(char *command, int *i, int *c, t_com *comm)
{
	*i = *i + 2;
	skip_to_the_next_word(command, i);
	while (command[*i] == '>')
		increment_both(i, c);
	if (*c > 2)
		*c = 2;
	if (comm->outkind != FILE_ERROR)
	{
		comm->outkind = FILE_ERROR;
		if (!command[*i] && *c == 0)
		{
			printf("syntax error near unexpected token `newline'\n");
			return (1);
		}
		printf("syntax error near unexpected token `");
		while (*c > 0)
		{
			*c = *c - 1;
			printf(">");
		}
		printf("\'\n");
	}
	return (0);
}

void	manage_bracketed_input(char *command, int *i, int *c, t_com *comm)
{
	skip_to_the_next_word(command, i);
	while (command[*i] == '<')
		increment_both(i, c);
	if (*c > 3)
		*c = 3;
	if (comm->entry != INPUT_ERROR)
	{
		comm->entry = INPUT_ERROR;
		printf("syntax error near unexpected token `");
		while (*c > 0)
		{
			*c = *c - 1;
			printf("<");
		}
		printf("\'\n");
	}
}

void	manage_empty_input(int *i, t_com *comm)
{
	if (comm->entry != INPUT_ERROR)
	{
		printf("syntax error near unexpected token `newline'\n");
		comm->entry = INPUT_ERROR;
	}
	*i = *i + 1;
}
