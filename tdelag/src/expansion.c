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

int	primary_exception_cancel(char *usr_input, int *i, int *l)
{
	if (is_whitespace(usr_input[*i + 1]) || first_character_env_invalid(usr_input[*i + 1]))
	{
		*l = *l + 2;
		*i = *i + 1;
		return (1);
	}
    if (is_numeric(usr_input[*i + 1]))
    {
        *i = *i + 2;
        return (1);
    }
	// if (usr_input[i + 1] == '?')
	// {
	// 	test_env_name = NULL;
	// 	env_var = ft_itoa(getpid());
	// 	i += 2;
	//	return (1)
	// }
	return (0);
}

void	get_length_dollar(char *usr_input, char **envp, int *i, int *l)
{
	int		j;
	char	*env_var;
	char	*test_env_name;

	if (primary_exception_cancel(usr_input, i, l))
		return ;
	*i = *i + 1;
	j = *i;
	test_env_name = NULL;
	while (usr_input[*i] && !(is_quote(usr_input[*i])) \
		&& !(is_whitespace(usr_input[*i])) \
		&& !(is_parasit(usr_input[*i])) && !is_delimiter(usr_input[*i]))
		*i = *i + 1;
	test_env_name = ft_strdupi(usr_input, &j, *i - j);
	env_var = get_env(envp, test_env_name);
	if (env_var)
	{
		*l = *l + ft_strlen(env_var);
		free(env_var);
		if (test_env_name)
			free(test_env_name);
		return ;
	}
	if (test_env_name)
		free(test_env_name);
}

void	single_quote_expansion(char *usr_input, int *i, int *l)
{
	int	j;

	j = *i;
	find_next_quote(usr_input, i, '\'', 1);
	*l = *l + (*i - j);
}

int	treat_the_char_exp(char *usr_input, int *i, int *l, bool *is_double_quote)
{
	if (usr_input[*i] == '\'' && !is_double_quote)
		single_quote_expansion(usr_input, i, l);
	else if (usr_input[*i] == '\"')
	{
		*is_double_quote = !(*is_double_quote);
		increment_both(i, l);
	}
	else if (usr_input[*i] == '$')
	{
		if (usr_input[*i + 1] == '$')
		{
			*i = *i + 2;
			return (0);
		}
		return (1);
	}
	else
		increment_both(i, l);
	return (0);
}

int	get_length_expanded(char *usr_input, char **envp)
{
	int		i;
	int		l;
	bool	is_double_quote;

	l = 0;
	i = 0;
	is_double_quote = false;
	while (usr_input[i])
		if (treat_the_char_exp(usr_input, &i, &l, &is_double_quote))
			get_length_dollar(usr_input, envp, &i, &l);
	return (l);
}
