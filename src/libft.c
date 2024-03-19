/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/05 16:44:14 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	should_add_quotes_child(const char *s, int *i, int *l, bool *reset)
{
	if (bis_quote((char *)s, *i))
    {
        *l = *l + 2;
        find_next_quote((char *) s, i, s[*i], 1);
    }
	else if (is_whitespace(s[*i]))
	{
		*reset = true;
		*i = *i + 1;
	}
	else
	{
		if (*reset)
		{
			*l = *l + 2;
			*reset = !(*reset);
		}
		*i = *i + 1;
	}
}

void	should_add_quotes(const char *s, char *cut, int *l)
{
	int		i;
	bool	reset;

	i = 0;
	reset = false;
	while (s[i] && cut[i] && s[i] == cut[i])
		i++;
	if (s[i] == '=')
		i++;
	while (s[i])
		should_add_quotes_child(s, &i, l, &reset);
}

void	quote_copy(const char *s, char **result, int *i, int *j)
{
	char	quote;

	quote = s[*i];
    (*result)[*j] = '\\';
    *j = *j + 1;
	(*result)[*j] = s[*i];
    increment_both(j, i);
	while (s[*i] != quote)
	{
		(*result)[*j] = s[*i];
        increment_both(j, i);
	}
    (*result)[*j] = '\\';
    *j = *j + 1;
	(*result)[*j] = s[*i];
    increment_both(j, i);
	return ;
}

void	ft_strdup_env_child(const char *s, t_dup_data *data, int *j, int *i)
{
	if (is_quote(s[*i]))
    {
        data->result[*j] = '\\';
        *j = *j + 1;
        data->result[*j] = s[*i];
        increment_both(j, i);
    }
	else if (is_whitespace(s[*i]))
	{
		if (!data->reset && data->multiple_word)
		{
			data->result[*j] = '\'';
			*j = *j + 1;
		}
		data->reset = true;
		dup_and_get_next((char **)&s, i, &data->result, j);
		data->multiple_word = true;
	}
	else if (!(bis_quote((char *)s, *i)) && !(is_whitespace(s[*i])) && data->reset)
	{
		data->result[*j] = '\'';
		*j = *j + 1;
		data->reset = !data->reset;
	}
	else
		dup_and_get_next((char **)&s, i, &data->result, j);
}

char	*ft_strdup_env(const char *s, char *cut, int i, int j)
{
	t_dup_data	data;

	data.multiple_word = false;
	data.reset = false;
	data.l = ft_strlen((char *)s) - (ft_strlen(cut) + 1);
	should_add_quotes(s, cut, &data.l);
	data.result = malloc((data.l + 1) * sizeof(char));
	if (!data.result)
		return (NULL);
	while (s[i] && cut[i] && s[i] == cut[i])
		i++;
	if (s[i] == '=')
		i++;
	while (s[i])
		ft_strdup_env_child(s, &data, &j, &i);
	if (!data.reset && data.multiple_word)
		data.result[j++] = '\'';
	data.result[j] = '\0';
	return (data.result);
}
