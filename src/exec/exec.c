/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:27:40 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/08 05:13:41 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cmd(struct s_cmd *cmd)
{
	char		*arg1;
	struct stat	buf;

	if (!cmd->exec)
		ft_fprintf(STDERR, "minishell: null command (internal problem)\n");
	else if (!cmd->args && !cmd->args[0])
		ft_fprintf(STDERR, "minishell: null argumnt list (internal problem)\n");
	else
	{
		arg1 = cmd->args[0];
		if (ft_strchr(arg1, '/'))
		{
			if (stat(cmd->exec, &buf) == 0 && buf.st_mode & S_IFDIR)
				ft_fprintf(STDERR, "minishell: %s: is a directory\n", arg1);
			else if (execve(cmd->exec, cmd->args, cmd->env) < 0)
				ft_fprintf(STDERR, "minishell: %s: %s\n", arg1,
					strerror(errno));
		}
		else if (execve(cmd->exec, cmd->args, cmd->env) < 0)
			ft_fprintf(STDERR, "minishell: %s: unknown command\n", arg1);
	}
	free_cmd(cmd);
	exit(127);
}

void	exec_builtin_s(struct s_cmd *cmd)
{
	t_builtin_f	builtin;
	int			ret;

	builtin = get_builtin(cmd->exec);
	ret = builtin(ft_dt_len((void **)cmd->args), cmd->args, cmd->env);
	free_cmd(cmd);
	exit(ret);
}

void	exec(t_main *data, struct s_cmds_piped cmds, int id, int *pids)
{
	struct s_cmd	*cmd;

	free(pids);
	m_close(data->incpy);
	cmd = cmds.cmds[id];
	dup2(cmd->infd, STDIN);
	dup2(cmd->outfd, STDOUT);
	free_dt((void **)data->envp);
	free_cmds(cmds, id);
	if (cmd->infd != STDIN)
		m_close(cmd->infd);
	if (cmd->outfd != STDOUT)
		m_close(cmd->outfd);
	if (!data->commands_data[id]->has_program)
	{
		free_cmd(cmd);
		deinit_thgg(data);
		exit(0);
	}
	deinit_thgg(data);
	rl_clear_history();
	if (is_builtin(cmd->exec))
		exec_builtin_s(cmd);
	exec_cmd(cmd);
}
