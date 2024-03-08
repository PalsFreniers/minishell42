/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:23:36 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/08 11:50:16 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_in_solo(t_main *thgg, char ***envp, int *last, int *ret)
{
	struct s_mainloop	b_in;

	b_in = solo_b_in(thgg->commands_data[0], envp, *last);
	*last = b_in.last;
	*ret = b_in.cont;
}

struct				s_mainloop_p
{
	int				*last;
	int				*ret;
};

struct s_mainloop	exec_cmds(t_main *thgg, char ***envp, struct s_mainloop_p m)
{
	if (!thgg)
		return ((struct s_mainloop){.cont = 0, .last = 1});
	if (thgg->command_c > 1)
	{
		*m.last = forks(thgg, *m.last);
	}
	else if (thgg->command_c == 1)
	{
		if (thgg->commands_data[0]->program
			&& is_builtin(thgg->commands_data[0]->program))
			b_in_solo(thgg, envp, m.last, m.ret);
		else
			*m.last = forks(thgg, *m.last);
	}
	return ((struct s_mainloop){.cont = *m.ret, .last = *m.last});
}

struct s_mainloop	free_and_set_mainloop(char *usr_input,
		struct s_mainloop ret_ml)
{
	free(usr_input);
	return (ret_ml);
}

void	add_to_history(char *usr_input)
{
	if (ft_strlen(usr_input))
		add_history(usr_input);
}

struct s_mainloop	give_the_prompt(char ***envp, int last, int cpy)
{
	int					ret;
	char				*usr_input;
	t_main				*thgg;
	struct s_mainloop	ret_ml;

	ret = 1;
	usr_input = readline("$> ");
	if (g_signum == SIGINT)
		return (free_and_set_mainloop(usr_input, (struct s_mainloop){1, 130}));
	else if (!usr_input)
		return ((struct s_mainloop){.cont = 0, .last = 1});
	add_to_history(usr_input);
	if (is_usr_input_blank(usr_input))
		return (free_and_set_mainloop(usr_input, (struct s_mainloop){1, last}));
	usr_input = expansion(usr_input, *envp, last);
	if (usr_input && is_usr_input_blank(usr_input))
		return (free_and_set_mainloop(usr_input, (struct s_mainloop){1, 0}));
	if (!usr_input || check_usr_input_for_errors(usr_input))
		return (free_and_set_mainloop(usr_input, (struct s_mainloop){1, 2}));
	thgg = init_thgg(*envp, usr_input);
	thgg->incpy = cpy;
	ret_ml = exec_cmds(thgg, envp, (struct s_mainloop_p){&last, &ret});
	if (thgg)
		deinit_thgg(thgg);
	return (ret_ml);
}
