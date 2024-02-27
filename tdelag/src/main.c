/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/27 21:57:44 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					g_signum = 0;

struct				s_mainloop
{
	t_bool			cont;
	int				last;
};

bool	is_correct(char *tmp, int i)
{
	while (tmp[i])
	{
		if (!ft_isdigit(tmp[i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(tmp, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

struct s_mainloop	sb_exit_checks(t_com *command, int argc, t_u64 ret)
{
	if (ret > MIN_I64)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(command->arguments[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return ((struct s_mainloop){0, 2});
	}
	if (argc > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ((struct s_mainloop){1, 1});
	}
	else
		return ((struct s_mainloop){0, ft_atol(command->arguments[1])});
}

struct s_mainloop	sb_exit(t_com *command)
{
	int		argc;
	int		i;
	char	*tmp;
	t_u64	ret;

	argc = ft_dt_len((void **)command->arguments);
	i = 0;
	printf("exit\n");
	g_signum = SIGTRAP;
	if (argc > 1)
	{
		tmp = command->arguments[1];
		if (tmp[0] == '-' || tmp[0] == '+')
			i++;
		if (!is_correct(tmp, i))
			return ((struct s_mainloop){0, 2});
		ret = ft_atol(command->arguments[1] + i);
		return (sb_exit_checks(command, argc, ret));
	}
	return ((struct s_mainloop){0, 0});
}

struct s_mainloop	solo_b_in(t_com *command, char ***envp)
{
	struct s_mainloop	ret;
	int					argc;

	argc = ft_dt_len((void **)command->arguments);
	ret = (struct s_mainloop){1, 0};
	if (ft_strequ(command->program, "exit"))
		ret = sb_exit(command);
	else if (ft_strequ(command->program, "echo"))
		ret.last = b_echo(argc, command->arguments, *envp);
	else if (ft_strequ(command->program, "env"))
		ret.last = b_env(argc, command->arguments, *envp);
	else if (ft_strequ(command->program, "pwd"))
		ret.last = b_pwd(argc, command->arguments, *envp);
	return (ret);
}

struct s_mainloop	give_the_prompt(char ***envp, int last)
{
	int					ret;
	struct s_mainloop	b_in;
	char				*usr_input;
	t_main				*thgg;

	ret = 1;
	usr_input = readline("$> ");
	if (g_signum == SIGINT)
		return ((struct s_mainloop){.cont = 1, .last = 130});
	else if (!usr_input)
		return ((struct s_mainloop){.cont = 0, .last = 1});
	if (ft_strlen(usr_input))
		add_history(usr_input);
	if (is_usr_input_blank(usr_input))
		return ((struct s_mainloop){.cont = 1, .last = last});
	usr_input = expansion(usr_input, *envp);
	if (check_usr_input_for_errors(usr_input))
	{
		free(usr_input);
		return ((struct s_mainloop){.cont = 1, .last = 2});
	}
	thgg = init_thgg(*envp, usr_input);
	if (!thgg)
		return ((struct s_mainloop){.cont = 0, .last = 1});
	if (thgg->command_c > 1)
	{
		last = forks(thgg);
	}
	else if (thgg->command_c == 1)
	{
		if (is_builtin(thgg->commands_data[0]->program))
		{
			b_in = solo_b_in(thgg->commands_data[0], envp);
			last = b_in.last;
			ret = b_in.cont;
		}
		else
			last = forks(thgg);
	}
	deinit_thgg(thgg);
	return ((struct s_mainloop){.cont = ret, .last = last});
}

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

void	catch_quit(int sn)
{
	(void)sn;
	ft_putstr_fd("\b\b  \b\b", 1);
}

int	main(int argc, char **argv, char **envp)
{
	int					cpy;
	char				**envp_cpy;
	struct s_mainloop	ret;

	(void)argc;
	(void)argv;
	cpy = dup(0);
	signal(SIGINT, catch_int);
	signal(SIGQUIT, catch_quit);
	envp_cpy = ft_strdup_char_star(envp);
	ret.last = 0;
	ret.cont = 1;
	while (1)
	{
		ret = give_the_prompt(&envp_cpy, ret.last);
		if (!ret.cont)
			break ;
		if (g_signum == SIGINT)
		{
			dup2(cpy, 0);
			g_signum = 0;
		}
		if (g_signum == SIGTRAP)
			g_signum = 0;
	}
	free_double_char(envp_cpy);
	close(cpy);
	if (g_signum != SIGTRAP)
		printf("exit\n");
	return (ret.last);
}
