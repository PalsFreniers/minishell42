/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/13 13:40:39 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ask_for_dum_hd(char *input, int *j)
{
	char	*s;
	char	*c;

	s = get_the_next_arg(input, j);
	while (1)
	{
		c = readline("here_doc> ");
		if (!c)
			continue ;
		c[ft_strlenc(c, '\n') + 1] = 0;
		if (ft_strequ(c, s))
		{
			free(c);
			break ;
		}
		free(c);
	}
}

void	error_exit_hd(char *input, int i)
{
	int	j;

	j = 0;
	if (i == 1)
		return ;
	while (j < i)
	{
		if (is_quote(input[j]))
			find_next_quote(input, &j, input[j], 1);
		else if (input[j] == '<' && input[j + 1] == '<')
		{
			j += 2;
			ask_for_dum_hd(input, &j);
		}
		else
			j++;
	}
}
