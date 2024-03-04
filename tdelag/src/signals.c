/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:29:39 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/04 22:05:19 by tdelage          ###   ########.fr       */
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
