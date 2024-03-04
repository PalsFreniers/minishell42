/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/04 10:00:08 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_expanded(int l)
{
	int		i;
	char	*expanded;

	i = 0;
	expanded = malloc((l + 1) * sizeof(char));
	if (!expanded)
		return (NULL);
	i = 0;
	while (i <= l)
		expanded[i++] = '\0';
	return (expanded);
}

void	exp_single_quote(char *usr_input, int *i, char *expanded, int *j)
{
	dup_and_get_next(&usr_input, i, &expanded, j);
	while (usr_input[*i] && usr_input[*i] != '\'')
		dup_and_get_next(&usr_input, i, &expanded, j);
	dup_and_get_next(&usr_input, i, &expanded, j);
}

void	ask_case(char *expanded, int *j, int last)
{
	char	*integer;
	int		i;

	i = 0;
	integer = ft_itoa(last);
	while (integer[i])
	{
		expanded[*j] = integer[i];
		*j = *j + 1;
		i++;
	}
	free(integer);
	return ;
}

int	expansion_char_is_dollar(char *usr_input, int *i, t_data_e *exp, int *j)
{
	if (usr_input[*i + 1] == '?')
	{
		ask_case(exp->expanded, j, exp->last);
		*i = *i + 2;
		return (0);
	}
	if (usr_input[*i + 1] == '$' || is_numeric(usr_input[*i + 1]))
	{
		dup_and_get_next(&usr_input, i, &exp->expanded, j);
		dup_and_get_next(&usr_input, i, &exp->expanded, j);
		return (0);
	}
	if (is_quote(usr_input[*i + 1]) && !exp->is_double_quote)
	{
		*i = *i + 1;
		return (0);
	}
	if (is_whitespace(usr_input[*i + 1])
		|| first_character_env_invalid(usr_input[*i + 1]))
	{
		dup_and_get_next(&usr_input, i, &exp->expanded, j);
		return (0);
	}
	return (1);
}

char	*get_the_test_env(char *usr_input, int *i)
{
	int		k;
	char	*test_env_name;

	*i = *i + 1;
	k = *i;
	test_env_name = NULL;
	while (usr_input[*i] && !(is_quote(usr_input[*i]))
		&& !(is_whitespace(usr_input[*i])) && !(is_parasit(usr_input[*i]))
		&& !is_delimiter(usr_input[*i]))
		*i = *i + 1;
	test_env_name = ft_strdupi(usr_input, &k, *i - k);
	return (test_env_name);
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
