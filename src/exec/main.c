/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:16:03 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/08 11:46:49 by tdelage          ###   ########.fr       */
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
	if (!ft_strchr(exec, '/'))
		return (ft_strjoin("/", exec));
	return (ft_strdup(exec));
}

void	sig_quit(int signum)
{
	(void)signum;
	write(STDERR, "Quit\n", 5);
}

void	fork_loop(int *pids, struct s_cmds_piped cmds, t_main *data,
		struct s_mainloop i)
{
	pids[i.cont] = fork();
	if (!(pids[i.cont]))
		exec(data, cmds, i, pids);
	else
	{
		if (cmds.cmds[i.cont]->infd != STDIN)
			m_close(cmds.cmds[i.cont]->infd);
		if (cmds.cmds[i.cont]->outfd != STDOUT)
			m_close(cmds.cmds[i.cont]->outfd);
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
		fork_loop(pids, cmds, data, (struct s_mainloop){i, last});
	deinit_fork(pids, cmds, &ret);
	if (g_signum == SIGINT)
	{
		signal(SIGINT, catch_int);
		return (130);
	}
	return ((ret & 0xff00) >> 8);
}
