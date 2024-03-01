/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:16:03 by tdelage           #+#    #+#             */
/*   Updated: 2024/02/28 18:16:02 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>
#define MAX_FILE_TRIES 100

void	ft_file_name_rand(char file[20])
{
	char	*str;
	int		len;
	int		i;

	str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	len = ft_strlen(str);
	i = 4;
	ft_memcpy(file, "/tmp/", 5);
	while (++i < 20)
		file[i] = str[ft_rand(0, len - 1)];
}

char	*ft_find_path(char *exec, char **paths)
{
	char	*ret;
	char	*tmp;
	size_t	i;
	char	c;

	c = exec[0];
	i = 0;
	while (paths && (c != '.' || exec[1] != '/') && c != '/' && paths[i])
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

t_u8	is_builtin(char *exec)
{
	if (ft_strequ(exec, "echo"))
		return (TRUE);
	if (ft_strequ(exec, "cd"))
		return (TRUE);
	if (ft_strequ(exec, "pwd"))
		return (TRUE);
	if (ft_strequ(exec, "export"))
		return (TRUE);
	if (ft_strequ(exec, "unset"))
		return (TRUE);
	if (ft_strequ(exec, "env"))
		return (TRUE);
	if (ft_strequ(exec, "exit"))
		return (TRUE);
	return (FALSE);
}

t_builtin_f	get_builtin(char *exec)
{
	if (ft_strequ(exec, "echo"))
		return (b_echo);
	if (ft_strequ(exec, "cd"))
		return (NULL);
	if (ft_strequ(exec, "pwd"))
		return (b_pwd);
	if (ft_strequ(exec, "export"))
		return (NULL);
	if (ft_strequ(exec, "unset"))
		return (b_unset);
	if (ft_strequ(exec, "env"))
		return (b_env);
	if (ft_strequ(exec, "exit"))
		return (b_exit);
	return (NULL);
}

void	generate_non_existing_file(char file[20])
{
	int	i;

	i = 0;
	ft_file_name_rand(file);
	while (++i < MAX_FILE_TRIES && access(file, F_OK) == 0)
		ft_file_name_rand(file);
}

void	write_heredoc(int fd, char *limiter, t_bool exp, char **envp)
{
	char	*c;
	char	*tmp;

	while (1)
	{
		ft_printf("%s ", limiter);
		c = readline("here_doc> ");
		if (!c)
			continue ;
		c[ft_strlenc(c, '\n') + 1] = 0;
		if (ft_strequ(c, limiter))
		{
			free(c);
			break ;
		}
		if (exp)
		{
			tmp = c;
			c = expansion(tmp, envp);
		}
		ft_fprintf(fd, "%s\n", c);
		free(c);
	}
}

int	make_here_doc_file(char *limiter, t_bool exp, char **env)
{
	char	file[21];
	int		fd;

	generate_non_existing_file(file);
	file[20] = 0;
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (fd);
	write_heredoc(fd, limiter, exp, env);
	m_close(fd);
	fd = open(file, O_RDONLY, 0644);
	if (fd == -1)
		return (fd);
	unlink(file);
	return (fd);
}

t_bool	ft_create_pipes(int (*pipes)[2], int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (pipe(pipes[i]) < 0)
		{
			while (--i >= 0)
			{
				m_close(pipes[i][0]);
				m_close(pipes[i][1]);
			}
			return (FALSE);
		}
	}
	return (TRUE);
}

void	close_all_pipes(int (*pipes)[2], int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		m_close(pipes[i][0]);
		m_close(pipes[i][1]);
	}
}

struct s_cmd	extract_base_cmd(t_main *data, int id)
{
	struct s_cmd	command;

	if (!is_builtin(data->commands_data[id]->program)
		&& ft_strlen(data->commands_data[id]->program) > 0)
		command.exec = ft_find_path(data->commands_data[id]->program,
				data->paths);
	else
		command.exec = ft_strdup(data->commands_data[id]->program);
	command.args = dup_char_dt(data->commands_data[id]->arguments);
	command.env = dup_char_dt(data->envp);
	return (command);
}

int	resolve_heredoc(char **hdd, t_bool all_dum, t_bool exp, char **env)
{
	int	ret;

	ret = -1;
	printf("resolve_heredoc all_dum %d\n", all_dum);
	resolve_dum_heredoc(hdd, all_dum);
	if (all_dum)
		ret = make_here_doc_file(hdd[ft_dt_len((void **)hdd) - 1], exp, env);
	return (ret);
}

int	resolve_entry(t_com *self, int (*pipes)[2], int id, char **env)
{
	int	ret;
	int	hd;

	if (self->has_heredoc)
		hd = resolve_heredoc(self->here_doc_delimiter,
				self->entry == ENTRY_HEREDOC, self->expand_hd, env);
	if (self->entry == ENTRY_PIPE)
		ret = pipes[id - 1][0];
	else if (self->entry == ENTRY_INPUT)
		ret = self->fd_input;
	else if (self->entry == NO_ENTRY)
		ret = STDIN;
	else if (self->entry == ENTRY_HEREDOC)
		ret = hd;
	else
		ret = -1;
	return (ret);
}

int	resolve_out(t_com *self, int (*pipes)[2], int id)
{
	int	ret;

	if (self->exit == EXIT_PIPE)
		ret = pipes[id][1];
	else if (self->exit == EXIT_OUTPUT)
		ret = self->fd_output;
	else if (self->exit == EXIT_STDOUT)
		ret = STDOUT;
	else
		ret = -1;
	return (ret);
}

struct s_cmd	*generate_cmd(t_main *data, int (*pipes)[2], int id)
{
	struct s_cmd	*command;
	t_com			*self;

	command = malloc(sizeof(struct s_cmd));
	*command = extract_base_cmd(data, id);
	self = data->commands_data[id];
	command->infd = resolve_entry(self, pipes, id, data->envp);
	command->outfd = resolve_out(self, pipes, id);
	return (command);
}

void	generate_fork_data(struct s_cmds_piped *self, t_main *data)
{
	int	i;

	i = -1;
	self->valid = TRUE;
	self->count = data->command_c;
	self->cmds = NULL;
	self->pipes = malloc((self->count - 1) * sizeof(int[2]));
	if (self->pipes)
	{
		self->valid = ft_create_pipes(self->pipes, self->count - 1);
		self->cmds = malloc((data->command_c + 1) * sizeof(struct s_cmd *));
		if (self->valid && self->cmds)
			while (++i < self->count)
				self->cmds[i] = generate_cmd(data, self->pipes, i);
		else
			self->valid = FALSE;
	}
	else
		self->valid = FALSE;
}

void	free_cmd(struct s_cmd *cmd)
{
	free_dt((void **)cmd->args);
	free_dt((void **)cmd->env);
	free(cmd->exec);
	free(cmd);
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
		if ((arg1[0] == '.' && arg1[1] == '/') || arg1[0] == '/')
		{
			if (stat(cmd->exec, &buf) == 0 && buf.st_mode & S_IFDIR)
				ft_fprintf(STDERR, "minishell: '%s': is a directory\n", arg1);
			else if (execve(cmd->exec, cmd->args, cmd->env) < 0)
				ft_fprintf(STDERR, "minishell: '%s': %s\n", arg1,
					strerror(errno));
		}
		else if (execve(cmd->exec, cmd->args, cmd->env) < 0)
			ft_fprintf(STDERR, "minishell: '%s': unknown command\n", arg1);
	}
	free_cmd(cmd);
	exit(127);
}

void	exec_builtin(struct s_cmd *cmd)
{
	t_builtin_f	builtin;
	int			ret;

	builtin = get_builtin(cmd->exec);
	ret = builtin(ft_dt_len((void **)cmd->args), cmd->args, cmd->env);
	free_cmd(cmd);
	exit(ret);
}

void	exec(t_main *data, struct s_cmds_piped cmds, int id)
{
	struct s_cmd	*cmd;

	cmd = cmds.cmds[id];
	dup2(cmd->infd, STDIN);
	dup2(cmd->outfd, STDOUT);
	free_dt((void **)data->envp);
	deinit_thgg(data);
	free_cmds(cmds, id);
	if (cmd->infd != STDIN)
		m_close(cmd->infd);
	if (cmd->outfd != STDOUT)
		m_close(cmd->outfd);
	if (!data->commands_data[id]->has_program)
	{
		free_cmd(cmd);
		return ;
	}
	if (is_builtin(cmd->exec))
		exec_builtin(cmd);
	exec_cmd(cmd);
}

int	forks(t_main *data)
{
	struct s_cmds_piped	cmds;
	int					*pids;
	int					i;
	int					ret;

	generate_fork_data(&cmds, data);
	if (!cmds.valid)
	{
		free_cmds(cmds, -1);
		return (127);
	}
	pids = malloc(cmds.count * sizeof(int));
	i = -1;
	while (++i < cmds.count)
	{
		pids[i] = fork();
		if (!(pids[i]))
			exec(data, cmds, i);
		else
		{
			if (cmds.cmds[i]->infd != STDIN)
				m_close(cmds.cmds[i]->infd);
			if (cmds.cmds[i]->outfd != STDOUT)
				m_close(cmds.cmds[i]->outfd);
		}
	}
	close_all_pipes(cmds.pipes, cmds.count - 1);
	i = -1;
	while (++i < cmds.count)
		waitpid(pids[i], &ret, 0);
	free_cmds(cmds, -1);
	free(pids);
	return ((ret & 0xff00) >> 8);
}
