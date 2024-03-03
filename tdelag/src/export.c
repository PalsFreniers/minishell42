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
	j = 0;
	if (is_numeric(test_name[j]) || first_character_env_invalid(test_name[j]))
	{
		free(test_name);
		return (false);
	}
	++j;
	while (test_name[j])
		++j;
	if (s[i] != '=' && !(s[i] == '+' && s[i + 1] == '='))
	{
		free(test_name);
		return (false);
	}
	free(test_name);
	return (true);
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

	if (s[*i] == '=')
		*i = *i + 1;
	else if (s[*i] == '+')
	{
		*type = PLUS;
		*i = *i + 2;
	}
	var_name = get_the_next_arg(s, i);
	return (var_name);
}

char	*get_the_var_name(char *s, int *i)
{
	int		i_bis;
	int		j;
	int		size;
	char	*var_name;

	i_bis = *i;
	size = 0;
	while (!(is_delimiter(s[i_bis])))
		increment_both(&size, &i_bis);
	var_name = malloc((size + 1) * sizeof(char));
	j = 0;
	while (j < size)
		dup_and_get_next(&s, i, &var_name, &j);
	var_name[j] = '\0';
	return (var_name);
}

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
	new_exp->var_value = get_the_var_value(argv[*index], &i, &new_exp->type);
	return (new_exp);
}

t_exp	**get_the_exps(int argc, char **argv, int count)
{
	int		i;
	int		index;
	t_exp	**exps;

	i = 0;
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
	big_exp->exp_count = count;
	big_exp->exps = get_the_exps(argc, argv, count);
	return (big_exp);
}

void	free_exp(t_exp *exp)
{
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
