#include "minishell.h"

typedef struct s_exp_actions{
    char *var_name;
    char *var_value;
}t_exp;

typedef struct s_global_expansion{
    int exp_count;
    t_exp **exps;
}t_big_exp;

bool    is_exp_struct(char *s)
{
    int i;

    i = 0;
    skip_to_the_next_word(s, &i);
    if (is_numeric(s[i]) || first_character_env_invalid(s[i]))
        return (false);
    ++i;
    while(s[i] && (!(first_character_env_invalid(s[i])) || is_numeric(s[i])))
        ++i;
    if (s[i] != '=')
        return (false);
    return (true);
}

int check_for_exp_c(int argc, char **argv)
{
    int     i;
    int     c;

    i = 1;
    c = 0;
    while (i < argc)
    {
        if (is_exp_struct(argv[i]))
            ++c;
        i++;
    }
    return (c);
}

char    *get_the_var_value(char *s, int *i)
{
    int i_bis;
    int j;
    int size;
    char *var_name;

    if (s[*i] == '=')
        *i = *i + 1;
    var_name = get_the_next_arg(s, i);
    return (var_name);
}

char    *get_the_var_name(char *s, int *i)
{
    int i_bis;
    int j;
    int size;
    char *var_name;

    i_bis = *i;
    size = 0;
    while(!(is_delimiter(s[i_bis])))
        increment_both(&size, &i_bis);
    var_name = malloc((size + 1) * sizeof(char));
    j = 0;
    while (j < size)
        dup_and_get_next(&s, i, &var_name, &j);
    var_name[j] = '\0';
    return (var_name);
}

t_exp       *get_an_exp(char **argv, int *index)
{
    int     i;
    t_exp   *new_exp;

    i = 0;
    while (argv[*index] && !(is_exp_struct(argv[*index])))
        *index = *index + 1;
    if (!argv[*index])
        return (NULL);
    new_exp = malloc(sizeof(t_exp));
    new_exp->var_name = get_the_var_name(argv[*index], &i);
    new_exp->var_value = get_the_var_value(argv[*index], &i);
    return (new_exp);
}

t_exp       **get_the_exps(int argc, char **argv, int count)
{
    int     i;
    int     index;
    t_exp   **exps;

    i = 0;
    index = 0;
    exps = malloc((count + 1) * sizeof(t_exp));
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

t_big_exp   *get_big_exp(int argc , char **argv)
{
    int     count;
    t_big_exp   *big_exp;

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