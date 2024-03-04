/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:16:03 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/04 22:11:06 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_find_path(char *exec, char **paths)
{
	char	*ret;
	char	*tmp;
	size_t	i;

	i = 0;
	while (paths && !ft_strchr(exec, '/') && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(tmp, exec);
		free(tmp);
		if (access(ret, F_OK | X_OK) == 0)
			return (ret);
		free(ret);
		i++;
	}
	return (ft_strdup(exec));
}

void	sig_quit(int signum)
{
	(void)signum;
	write(STDERR, "Quit (core dumped)\n", 19);
}

void	fork_loop(int *pids, struct s_cmds_piped cmds, t_main *data, int i)
{
	pids[i] = fork();
	if (!(pids[i]))
		exec(data, cmds, i, pids);
	else
	{
		if (cmds.cmds[i]->infd != STDIN)
			m_close(cmds.cmds[i]->infd);
		if (cmds.cmds[i]->outfd != STDOUT)
			m_close(cmds.cmds[i]->outfd);
	}
}

void	deinit_fork(int *pids, struct s_cmds_piped cmds, int *ret)
{
	int	i;

	close_all_pipes(cmds.pipes, cmds.count - 1);
	i = -1;
	while (g_signum != SIGINT && ++i < cmds.count)
		waitpid(pids[i], ret, 0);
	free_cmds(cmds, -1);
	free(pids);
}

int	forks(t_main *data, int last)
{
	struct s_cmds_piped	cmds;
	int					*pids;
	int					i;
	int					ret;

	generate_fork_data(&cmds, data, last);
	pids = malloc(cmds.count * sizeof(int));
	if (!cmds.valid || !pids)
	{
		free_cmds(cmds, -1);
		return (127);
	}
	i = -1;
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, catch_int);
	while (g_signum != SIGINT && ++i < cmds.count)
		fork_loop(pids, cmds, data, i);
	deinit_fork(pids, cmds, &ret);
	if (g_signum == SIGINT)
	{
		signal(SIGINT, catch_int);
		return (130);
	}
	return ((ret & 0xff00) >> 8);
}
