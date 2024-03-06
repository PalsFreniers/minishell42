/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_b_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:29:44 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/06 18:20:29 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_mainloop	reset_command(struct s_reset_vec reset_vec)
{
	dup2(reset_vec.c_stdin, 0);
	dup2(reset_vec.c_stdout, 1);
	m_close(reset_vec.c_stdin);
	m_close(reset_vec.c_stdout);
	return ((struct s_mainloop){1, 130});
}

struct s_reset_vec	prepare_command(t_com *command, char **envp, int last)
{
	int	c_stdin;
	int	c_stdout;
	int	in;
	int	out;

	c_stdin = dup(0);
	c_stdout = dup(1);
	in = resolve_entry(command, NULL, (struct s_mainloop){.cont = -1,
			.last = last}, envp);
	out = resolve_out(command, NULL, -1);
	dup2(in, 0);
	dup2(out, 1);
	if (in != STDIN)
		m_close(in);
	if (out != STDOUT)
		m_close(out);
	return ((struct s_reset_vec){c_stdin, c_stdout});
}

void	exec_builtin(t_com *command, struct s_mainloop *ret, char ***envp,
		int argc)
{
	if (ft_strequ(command->program, "exit"))
		*ret = sb_exit(command);
	else if (ft_strequ(command->program, "echo"))
		ret->last = b_echo(argc, command->arguments, *envp);
	else if (ft_strequ(command->program, "env"))
		ret->last = b_env(argc, command->arguments, *envp);
	else if (ft_strequ(command->program, "pwd"))
		ret->last = b_pwd(argc, command->arguments, *envp);
	else if (ft_strequ(command->program, "unset"))
		*ret = sb_unset(command, envp);
	else if (ft_strequ(command->program, "cd"))
		*ret = sb_cd(argc, command, envp);
	else if (ft_strequ(command->program, "export"))
		*ret = sb_export(envp, command);
}

struct s_mainloop	solo_b_in(t_com *command, char ***envp, int last)
{
	struct s_mainloop	ret;
	int					argc;
	struct s_reset_vec	reset_vec;

	if (!command)
		return ((struct s_mainloop){1, 0});
	argc = ft_dt_len((void **)command->arguments);
	ret = (struct s_mainloop){1, 0};
	reset_vec = prepare_command(command, *envp, last);
	if (g_signum == SIGINT)
		return (reset_command(reset_vec));
	if (command->has_program)
		exec_builtin(command, &ret, envp, argc);
	reset_command(reset_vec);
	return (ret);
}

bool	no_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (false);
		i++;
	}
	return (true);
}
