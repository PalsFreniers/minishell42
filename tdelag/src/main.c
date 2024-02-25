/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/24 11:29:42 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					g_signum = 0;

struct				s_mainloop
{
	t_bool			cont;
	int				last;
};

struct s_mainloop        solo_b_in(t_com *command)
{
        struct s_mainloop ret;

        ret = (struct s_mainloop){1, 0};
        if(ft_strequ(command->program, "exit"))
                ret = (struct s_mainloop){0, 0};
        return (ret);
}

struct s_mainloop	give_the_prompt(char ***envp, int last)
{
        int ret;
        struct s_mainloop b_in;
        char *usr_input;
        t_main *thgg;

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
			b_in = solo_b_in(thgg->commands_data[0]);
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
	}
	free_double_char(envp_cpy);
	printf("exit\n");
	return (ret.last);
}
