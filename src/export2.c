/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:31:25 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/08 01:28:41 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exp	*get_an_exp(char **argv, int *index)
{
	int		i;
	t_exp	*new_exp;

	i = 0;
	while (argv[*index] && !(is_exp_struct(argv[*index])))
		*index = *index + 1;
	if (!argv[*index])
		return (NULL);
	new_exp = malloc(sizeof(t_exp));
	if (!new_exp)
		return (NULL);
	new_exp->type = EQUAL;
	new_exp->var_name = get_the_exp_name(argv[*index], &i);
	if (!new_exp->var_name)
		return (NULL);
	new_exp->var_value = get_the_var_value(argv[*index], &i, &new_exp->type);
	return (new_exp);
}

t_exp	**get_the_exps(int argc, char **argv, int count)
{
	int		i;
	int		index;
	t_exp	**exps;

	i = 1;
	index = 0;
	if (argc == 1)
		return (NULL);
	exps = malloc((count + 1) * sizeof(t_exp));
	if (!exps)
		return (NULL);
	while (i < count)
	{
		exps[i] = get_an_exp(argv, &index);
		if (!(exps[i]))
			return (exps);
		increment_both(&i, &index);
	}
	exps[i] = NULL;
	return (exps);
}

t_big_exp	*get_big_exp(int argc, char **argv)
{
	int			count;
	t_big_exp	*big_exp;

	if (!(ft_strcmp("export", argv[0])))
		return (NULL);
	count = check_for_exp_c(argc, argv);
	if (!count)
		return (NULL);
	big_exp = malloc(sizeof(t_big_exp));
	if (!big_exp)
		return (NULL);
	big_exp->exp_count = count;
	big_exp->exps = get_the_exps(argc, argv, count);
	return (big_exp);
}

void	free_exp(t_exp *exp)
{
	if (!exp)
		return ;
	free(exp->var_name);
	free(exp->var_value);
	free(exp);
}

void	free_big_exp(t_big_exp *big_exp)
{
	int	i;

	i = 0;
	if (!big_exp || !big_exp->exps)
		return ;
	while (i < big_exp->exp_count)
	{
		free_exp(big_exp->exps[i]);
		++i;
	}
	free(big_exp->exps);
	free(big_exp);
}
