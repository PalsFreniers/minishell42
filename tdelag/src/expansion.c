/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/05 12:48:42 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	primary_exception_cancel(char *usr_input, int *i, int *l, int last)
{
	char	*r;

	if (usr_input[*i + 1] == '?')
	{
		r = (ft_itoa(last));
		*l = *l + ft_strlen(r);
		free(r);
		*i = *i + 2;
		return (1);
	}
	if (is_whitespace(usr_input[*i + 1])
		|| first_character_env_invalid(usr_input[*i + 1]))
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
	return (0);
}

bool	is_dollar_cut(char c)
{
	if (is_quote(c))
		return (1);
	if (is_whitespace(c))
		return (1);
	if (is_parasit(c))
		return (1);
	if (is_delimiter(c))
		return (1);
	return (0);
}

void	get_length_dollar(char *usr_input, char **envp, t_length_exp *data)
{
	int		j;
	char	*env_var;
	char	*test_env_name;

	if (primary_exception_cancel(usr_input, &(data->i), &(data->l), data->last))
		return ;
	data->i = data->i + 1;
	j = data->i;
	test_env_name = NULL;
	while (usr_input[data->i] && !(is_dollar_cut(usr_input[data->i])))
		data->i = data->i + 1;
	test_env_name = ft_strdupi(usr_input, &j, data->i - j);
	env_var = get_env(envp, test_env_name);
	if (env_var)
	{
		data->l = data->l + ft_strlen(env_var);
		free(env_var);
		if (test_env_name)
			free(test_env_name);
		return ;
	}
	if (test_env_name)
		free(test_env_name);
}

void	add_env_var(char *expanded, int *j, char *test_env_name, char **envp)
{
	char	*env_var;

	env_var = get_env(envp, test_env_name);
	if (env_var)
	{
		ft_str_append(&expanded, j, env_var);
		free(env_var);
		if (test_env_name)
			free(test_env_name);
		return ;
	}
	if (test_env_name)
		free(test_env_name);
}
