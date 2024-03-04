/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:21:52 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/04 21:43:03 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(struct s_cmd *cmd)
{
	if (!cmd)
		return ;
	free_dt((void **)cmd->args);
	free_dt((void **)cmd->env);
	free(cmd->exec);
	free(cmd);
}

void	close_all_pipes(int (*pipes)[2], int count)
{
	int	i;

	if (!pipes)
		return ;
	i = -1;
	while (++i < count)
	{
		m_close(pipes[i][0]);
		m_close(pipes[i][1]);
	}
}

void	free_cmds(struct s_cmds_piped piped, int skip)
{
	int	i;

	i = -1;
	if (piped.pipes)
	{
		close_all_pipes(piped.pipes, piped.count - 1);
		free(piped.pipes);
	}
	if (piped.cmds)
	{
		while (++i < piped.count)
		{
			if (i == skip)
				continue ;
			free_cmd(piped.cmds[i]);
		}
		free(piped.cmds);
	}
}
