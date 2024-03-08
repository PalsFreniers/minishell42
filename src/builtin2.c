/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:29:56 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/08 01:30:18 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_no_env(char *name, char ***envp)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (ft_dt_len((void **)*envp) + 2));
	if (!tmp)
		return ;
	i = -1;
	while ((*envp)[++i])
		tmp[i] = (*envp)[i];
	tmp[i] = ft_strdup(name);
	tmp[i + 1] = NULL;
	free(*envp);
	*envp = tmp;
}

void	create_append_env(t_exp *exp, char ***envp)
{
	char	*tmp;

	if (!exp)
		return ;
	if (exp->type == EQUAL)
	{
		remove_one(exp->var_name, envp);
		create_env(exp->var_name, exp->var_value, envp);
	}
	else if (exp->type == PLUS)
	{
		tmp = ft_strjoin(exp->var_value, get_env_value_view(exp->var_name,
					*envp));
		if (!tmp)
			return ;
		remove_one(exp->var_name, envp);
		create_env(exp->var_name, tmp, envp);
		free(tmp);
	}
	else if (exp->type == NOTHING)
	{
		if (is_env(exp->var_name, *envp))
			return ;
		create_no_env(exp->var_name, envp);
	}
}

struct s_mainloop	sb_export(char ***envp, t_com *command)
{
	t_big_exp	*exp;
	int			i;
	int			argc;
	int			ret;

	ret = 0;
	argc = ft_dt_len((void **)command->arguments);
	if (argc == 1)
		return (print_export(*envp));
	b_export(argc, command->arguments, *envp);
	exp = get_big_exp(argc, command->arguments);
	if (!exp)
		return ((struct s_mainloop){1, 1});
	i = 0;
        printf("export_count: %d\n", exp->exp_count);
	while (i < exp->exp_count)
	{
		create_append_env(exp->exps[i], envp);
		i++;
	}
	free_big_exp(exp);
	return ((struct s_mainloop){1, 0});
}

char	*get_cd_path(int argc, t_com *command, char **envp)
{
	char	*path;

	if (argc == 1)
	{
		path = get_env_value_view("HOME", envp);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
	}
	else if (ft_strequ(command->arguments[1], "-"))
	{
		path = get_env_value_view("OLDPWD", envp);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
	}
	else
		path = command->arguments[1];
	return (path);
}

struct s_mainloop	sb_cd(int argc, t_com *command, char ***envp)
{
	char	*path;

	path = get_cd_path(argc, command, *envp);
	if (path == NULL)
		return ((struct s_mainloop){1, 1});
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
