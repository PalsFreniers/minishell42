/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/13 13:40:39 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_expansion(t_data_e *exp, char *usr_input, char **envp)
{
	if (expansion_char_is_dollar(usr_input, &exp->i, exp, &exp->j))
	{
		exp->test_env_name = get_the_test_env(usr_input, &exp->i);
		add_env_var(exp->expanded, &exp->j, exp->test_env_name, envp);
	}
}

char	*get_expanded(char *usr_input, char **envp, int expansion_l)
{
	t_data_e	exp;

	exp.is_double_quote = false;
	exp.expanded = create_expanded(expansion_l);
	exp.i = 0;
	exp.j = 0;
	while (usr_input[exp.i])
	{
		if (usr_input[exp.i] == '\'' && !exp.is_double_quote)
			exp_single_quote(usr_input, &exp.i, exp.expanded, &exp.j);
		else if (usr_input[exp.i] == '\"')
		{
			exp.is_double_quote = !exp.is_double_quote;
			exp.expanded[exp.j++] = usr_input[exp.i++];
		}
		else if (usr_input[exp.i] == '$')
			create_expansion(&exp, usr_input, envp);
		else
			exp.expanded[exp.j++] = usr_input[exp.i++];
	}
	return (exp.expanded);
}

char	*expansion(char *usr_input, char **envp)
{
	char	*expanded_input;
	size_t	expanded_l;

	expanded_l = get_length_expanded(usr_input, envp);
	if (expanded_l == ft_strlen(usr_input))
		return (usr_input);
	expanded_input = get_expanded(usr_input, envp, expanded_l);
	free(usr_input);
	return (expanded_input);
}
