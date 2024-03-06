/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/05 12:18:03 by dosokin          ###   ########.fr       */
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

void	exp_heredoc(char *usr_input, int *i, char *expanded, int *j)
{
	int	tempo;

	dup_and_get_next(&usr_input, i, &expanded, j);
	dup_and_get_next(&usr_input, i, &expanded, j);
	tempo = *i;
	skip_the_next_word(usr_input, i);
	while (tempo < *i)
		dup_and_get_next(&usr_input, &tempo, &expanded, j);
}

void	find_exp_parts(t_data_e *exp, char *usr_input, char **envp)
{
	if (usr_input[exp->i] == '\'' && !exp->is_double_quote)
		exp_single_quote(usr_input, &exp->i, exp->expanded, &exp->j);
	else if (usr_input[exp->i] == '\"')
	{
		exp->is_double_quote = !exp->is_double_quote;
		exp->expanded[exp->j++] = usr_input[exp->i++];
	}
	else if (usr_input[exp->i] == '$')
		create_expansion(exp, usr_input, envp);
	else if (!exp->is_double_quote && (usr_input[exp->i] == '<'
			&& usr_input[exp->i + 1] == '<'))
		exp_heredoc(usr_input, &exp->i, exp->expanded, &exp->j);
	else
		exp->expanded[exp->j++] = usr_input[exp->i++];
}

char	*get_expanded(char *usr_input, char **envp, int expansion_l, int last)
{
	t_data_e	exp;

	exp.is_double_quote = false;
	exp.expanded = create_expanded(expansion_l);
	if (!exp.expanded)
		return (NULL);
	exp.i = 0;
	exp.j = 0;
	exp.last = last;
	while (usr_input[exp.i])
		find_exp_parts(&exp, usr_input, envp);
	return (exp.expanded);
}

char	*expansion(char *usr_input, char **envp, int last)
{
	char	*expanded_input;
	size_t	expanded_l;

	expanded_l = get_length_expanded(usr_input, envp, last);
	if (expanded_l == ft_strlen(usr_input) && no_dollar(usr_input))
		return (usr_input);
	expanded_input = get_expanded(usr_input, envp, expanded_l, last);
	free(usr_input);
	if (!expanded_input)
		return (NULL);
	return (expanded_input);
}
