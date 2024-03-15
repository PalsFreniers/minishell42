/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:27:40 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/08 11:39:31 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_file(char *arg1, struct s_cmd *cmd, int *ret)
{
	struct stat	buf;

	if (stat(cmd->exec, &buf) == 0 && buf.st_mode & S_IFDIR)
	{
		*ret = 126;
		ft_fprintf(STDERR, "minishell: %s: Is a directory\n", arg1);
	}
	else if (execve(cmd->exec, cmd->args, cmd->env) < 0)
		ft_fprintf(STDERR, "minishell: %s: %s\n", arg1, strerror(errno));
	if (access(cmd->exec, F_OK) == -1)
		*ret = 127;
	else if (access(cmd->exec, X_OK) == -1)
		*ret = 126;
}

void	exec_cmd(struct s_cmd *cmd)
{
	char	*arg1;
	int		ret;

	ret = 127;
	if (!cmd->exec)
		ft_fprintf(STDERR, "minishell: null command (internal problem)\n");
	else if (!cmd->args && !cmd->args[0])
		ft_fprintf(STDERR, "minishell: null argumnt list (internal problem)\n");
	else
	{
		arg1 = cmd->args[0];
		if (ft_strchr(arg1, '/'))
			exec_file(arg1, cmd, &ret);
		else if (execve(cmd->exec, cmd->args, cmd->env) < 0)
			ft_fprintf(STDERR, "minishell: %s: command not found\n", arg1);
	}
	free_cmd(cmd);
	exit(ret);
}

void	exec_builtin_s(struct s_cmd *cmd, int l)
{
	t_builtin_f	builtin;
	int			ret;

	builtin = get_builtin(cmd->exec);
	if (!ft_strequ(cmd->exec, "exit"))
		ret = builtin(ft_dt_len((void **)cmd->args), cmd->args, cmd->env);
	else
		ret = b_exit(ft_dt_len((void **)cmd->args), cmd->args, cmd->env, l);
	free_cmd(cmd);
	exit(ret);
}

void	dup_2(struct s_cmd *cmd)
{
	dup2(cmd->infd, STDIN);
	dup2(cmd->outfd, STDOUT);
	if (cmd->infd != STDIN)
		m_close(cmd->infd);
	if (cmd->outfd != STDOUT)
		m_close(cmd->outfd);
}

void	exec(t_main *data, struct s_cmds_piped cmds, struct s_mainloop id,
		int *pids)
{
	struct s_cmd	*cmd;
	int				i;

	free(pids);
	m_close(data->incpy);
	cmd = cmds.cmds[id.cont];
	dup_2(cmd);
	free_dt((void **)data->envp);
	free_cmds(cmds, id.cont);
	if (!data->commands_data[id.cont]->has_program)
	{
		i = data->commands_data[id.cont]->error != 0;
		free_cmd(cmd);
		deinit_thgg(data);
		exit(i);
	}
	deinit_thgg(data);
	rl_clear_history();
	if (is_builtin(cmd->exec))
		exec_builtin_s(cmd, id.last);
	exec_cmd(cmd);
}
