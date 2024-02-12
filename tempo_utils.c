/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 11:10:58 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*entry_to_text(t_entry entry)
{
	static char	*table[] = {
		"ENTRY_HEREDOC",
		"ENTRY_INPUT",
		"ENTRY_PIPE",
		"NO_ENTRY",
		"HD_ERROR",
	};

	return (table[entry]);
}

char	*exit_to_text(t_exit exit)
{
	static char	*table[] = {
		"EXIT_OUTPUT",
		"EXIT_PIPE",
		"EXIT_STDOUT",
	};

	return (table[exit]);
}
