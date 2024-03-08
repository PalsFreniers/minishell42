/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/08 05:39:28 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signum = 0;

void	prompt_loop_prepare(struct s_mainloop *ret, char ***envp, int cpy)
{
	signal(SIGQUIT, SIG_IGN);
	*ret = give_the_prompt(envp, ret->last, cpy);
}

void	prompt_loop_signals(int cpy)
{
	if (g_signum == SIGINT)
	{
		dup2(cpy, 0);
		g_signum = 0;
	}
	if (g_signum == SIGTRAP)
		g_signum = 0;
}

void	init_rand(void)
{
	int	ps;

	ps = fork();
	if (ps == 0)
		exit(0);
	waitpid(ps, NULL, 0);
	ft_srand(ps);
}

char	**envp_set(char **envp)
{
	char	**envp_cpy;

	envp_cpy = ft_strdup_char_star(envp);
	if (!ft_getenv("PATH", envp))
		create_env("PATH",
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
			&envp_cpy);
	return (envp_cpy);
}

int	main(int argc, char **argv, char **envp)
{
	int					cpy;
	char				**envp_cpy;
	struct s_mainloop	ret;

	(void)argc;
	(void)argv;
	init_rand();
	cpy = dup(0);
	signal(SIGINT, catch_int);
	envp_cpy = envp_set(envp);
	if (!envp_cpy)
		return (0);
	ret = (struct s_mainloop){.cont = 1, .last = 0};
	while (1)
	{
		prompt_loop_prepare(&ret, &envp_cpy, cpy);
		if (!ret.cont)
			break ;
		prompt_loop_signals(cpy);
	}
	free_all_main(cpy, envp_cpy);
	if (g_signum != SIGTRAP)
		printf("exit\n");
	return (ret.last);
}
