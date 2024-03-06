/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:13:13 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/06 20:32:42 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_the_exp_name_l(char *command, int j)
{
	int	length;
	int	tempo;

	length = 0;
	if (is_quote(command[j]))
	{
		tempo = j;
		find_next_quote(command, &j, command[j], 1);
		length = length + (j - tempo - 2);
		if (!is_whitespace(command[j]) && command[j] != '=')
			return (length + get_the_exp_name_l(command, j));
		return (length);
	}
	while (command[j] && ((!(first_character_env_invalid(command[j]))
				|| is_numeric(command[j])) || is_quote(command[j]))
		&& command[j] != '=')
	{
		if (is_quote(command[j]))
			return (length + get_the_exp_name_l(command, j));
		++length;
		++j;
	}
	return (length);
}

char	*get_the_exp_name(char *command, int *i)
{
	char	*argument;
	int		length;
	char	type_quote;
	int		j;

	type_quote = 'a';
	length = get_the_exp_name_l(command, *i);
	argument = malloc((length + 1) * sizeof(char));
	if (!argument)
		return (NULL);
	j = 0;
	while (j < length)
	{
		if (is_quote(command[*i]))
		{
			if (!(gtna_quote_case(command, i, &type_quote)))
				dup_and_get_next(&command, i, &argument, &j);
		}
		else
			dup_and_get_next(&command, i, &argument, &j);
	}
	argument[j] = '\0';
	skip_ending_quotes(command, i, length);
	return (argument);
}

bool	is_exp_struct(char *s)
{
	int		i;
	int		j;
	char	*test_name;

	i = 0;
	skip_to_the_next_word(s, &i);
	test_name = get_the_exp_name(s, &i);
	if (!test_name)
		return (false);
	j = 0;
	if (is_numeric(test_name[j]) || first_character_env_invalid(test_name[j]))
	{
		free(test_name);
		return (false);
	}
	free(test_name);
	if (!s[i] || is_whitespace(s[i]) || s[i] == '=' || (s[i] == '+' && s[i
				+ 1] == '='))
		return (true);
	return (false);
}

int	check_for_exp_c(int argc, char **argv)
{
	int	i;
	int	c;

	i = 1;
	c = 0;
	while (i < argc)
	{
		if (!argv[i])
			return (c);
		if (is_exp_struct(argv[i]))
			++c;
		i++;
	}
	return (c);
}

char	*get_the_var_value(char *s, int *i, t_exp_type *type)
{
	char	*var_name;

	if (!s[*i] || is_whitespace(s[*i]))
	{
		*type = NOTHING;
		return (NULL);
	}
	if (s[*i] == '=')
		*i = *i + 1;
	else if (s[*i] == '+')
	{
		*type = PLUS;
		*i = *i + 2;
	}
	var_name = ft_strdup(s + *i);
	return (var_name);
}
