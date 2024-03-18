/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:29:39 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/08 05:35:14 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_int2(int sn)
{
	g_signum = sn;
	close(0);
}

void	catch_int(int sn)
{
	g_signum = sn;
	printf("\n");
	signal(SIGINT, catch_int2);
	close(0);
}

void	free_all_main(int cpy, char **envp_cpy)
{
	clear_history();
	free_double_char(envp_cpy);
	close(cpy);
}
