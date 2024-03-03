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

t_bool	is_env(char *arg, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(arg, envp[i], ft_strlen(arg)) == 0
			&& envp[i][ft_strlen(arg)] == '=')
			return (TRUE);
	}
	return (FALSE);
}

void	remove_one(char *argument, char ***envp)
{
	char	**tmp;
	int		j;
	int		k;

	if (is_env(argument, *envp))
	{
		tmp = malloc(sizeof(char *) * (ft_dt_len((void **)*envp)));
		j = -1;
		k = -1;
		while ((*envp)[++j])
		{
			if (ft_strncmp(argument, (*envp)[j], ft_strlen(argument)) != 0)
				tmp[++k] = ft_strdup((*envp)[j]);
		}
		free_dt((void **)*envp);
		*envp = tmp;
	}
}

struct s_mainloop	sb_unset(t_com *command, char ***envp)
{
	int	i;

	i = 0;
	while (command->arguments[++i])
		remove_one(command->arguments[i], envp);
	return ((struct s_mainloop){1, 0});
}

char	*get_env_value_view(char *name, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(name, envp[i], ft_strlen(name)) == 0)
			return (envp[i] + ft_strlen(name) + 1);
	return (NULL);
}

void	create_env(char *name, char *value, char ***envp)
{
	char	**tmp;
	char	*tmp2;
	int		i;

	tmp = malloc(sizeof(char *) * (ft_dt_len((void **)*envp) + 2));
	i = -1;
	while ((*envp)[++i])
		tmp[i] = (*envp)[i];
	tmp2 = ft_strjoin(name, "=");
	tmp[i] = ft_strjoin(tmp2, value);
	free(tmp2);
	tmp[i + 1] = NULL;
	free(*envp);
	*envp = tmp;
}

char	**sort_env(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	envp = dup_char_dt(envp);
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}

struct s_mainloop	print_export(char **envp)
{
	int	i;
	int	j;

	i = -1;
	envp = sort_env(envp);
	if (!envp)
		return ((struct s_mainloop){1, 1});
	while (envp[++i])
	{
		j = -1;
		ft_putstr_fd("declare -x ", 1);
		while (envp[i][++j] != '=')
			ft_putchar_fd(envp[i][j], 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(envp[i] + j + 1, 1);
		ft_putstr_fd("\"\n", 1);
	}
	free_dt((void **)envp);
	return ((struct s_mainloop){1, 0});
}

struct s_mainloop	sb_export(char ***envp, t_com *command)
{
	t_big_exp	*exp;
	int			i;
	char		*tmp;
	int			argc;

	argc = ft_dt_len((void **)command->arguments);
	if (argc == 1)
		return (print_export(*envp));
	// add checks
	exp = get_big_exp(argc, command->arguments);
	if (!exp)
		return ((struct s_mainloop){1, 1});
	i = 0;
	while (i < exp->exp_count)
	{
                printf("%s\n", exp->exps[i]->var_name);
		if (exp->exps[i]->type == EQUAL)
		{
			remove_one(exp->exps[i]->var_name, envp);
			create_env(exp->exps[i]->var_name, exp->exps[i]->var_value, envp);
		}
		else if (exp->exps[i]->type == PLUS)
		{
			tmp = ft_strjoin(exp->exps[i]->var_value,
				get_env_value_view(exp->exps[i]->var_name, *envp));
			remove_one(exp->exps[i]->var_name, envp);
			create_env(exp->exps[i]->var_name, tmp, envp);
                        free(tmp);
		}
		i++;
	}
	return ((struct s_mainloop){1, 0});
}

struct s_mainloop	sb_cd(int argc, t_com *command, char ***envp)
{
	char	*path;

	if (argc == 1)
	{
		path = get_env_value_view("HOME", *envp);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ((struct s_mainloop){1, 1});
		}
	}
	else
		path = command->arguments[1];
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return ((struct s_mainloop){1, 1});
	}
	remove_one("OLDPWD", envp);
	create_env("OLDPWD", get_env_value_view("PWD", *envp), envp);
	path = getcwd(NULL, 0);
	remove_one("PWD", envp);
	create_env("PWD", path, envp);
	free(path);
	return ((struct s_mainloop){1, 0});
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
	else if (ft_strequ(command->program, "unset"))
		ret = sb_unset(command, envp);
	else if (ft_strequ(command->program, "cd"))
		ret = sb_cd(argc, command, envp);
	else if (ft_strequ(command->program, "export"))
		ret = sb_export(envp, command);
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
