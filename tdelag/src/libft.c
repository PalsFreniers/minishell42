/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/13 10:41:20 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strbackslashn(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\n')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		l;
	int		i;
	char	*k;

	i = 0;
	l = ft_strlen((char *)s);
	k = malloc((l + 1) * (sizeof(const char)));
	if (k == NULL)
		return (NULL);
	while (s[i])
	{
		k[i] = s[i];
		i++;
	}
	k[i] = '\0';
	return (k);
}

void	should_add_quotes(const char *s, char *cut, int *l)
{
	int		i;
	bool	reset;

	i = 0;
	reset = true;
	while (s[i] && cut[i] && s[i] == cut[i])
		i++;
	if (s[i] == '=')
		i++;
	while (s[i])
	{
		if (is_quote(s[i]))
			find_next_quote((char *)s, &i, s[i], 1);
		else if (is_whitespace(s[i]))
			reset = true;
		else
		{
			if (reset)
			{
				*l = *l + 2;
				reset = !reset;
			}
			i++;
		}
	}
}

void	quote_copy(const char *s, char **result, int *i, int *j)
{
	char quote;

	quote = s[*i];
	(*result)[*j] = s[*i];
	*j = *j + 1;
	*i = *i + 1;
	while (s[*i] != quote)
	{
		(*result)[*j] = s[*i];
		*j = *j + 1;
		*i = *i + 1;
	}
	(*result)[*j] = s[*i];
	*j = *j + 1;
	*i = *i + 1;
	return ;
}

char	*ft_strdup_env(const char *s, char *cut, int i, int j)
{
	int		l;
	char	*result;
	bool	reset;

	reset = true;
	l = ft_strlen((char *)s) - (ft_strlen(cut) + 1);
	should_add_quotes(s, cut, &l);
	result = malloc((l + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s[i] && cut[i] && s[i] == cut[i])
		i++;
	if (s[i] == '=')
		i++;
	while (s[i])
	{
		if (is_quote(s[i]))
			quote_copy(s, &result, &i, &j);
		else if (is_whitespace(s[i]))
		{
			if (!reset)
				result[j++] = '\'';
			reset = true;
			result[j++] = s[i++];
		}
		else if (!(is_quote(s[i])) && !(is_whitespace(s[i])) && reset)
		{
			result[j++] = '\'';
			reset = !reset;
		}
		else
			result[j++] = s[i++];
	}
	if (!reset)
		result[j++] = '\'';
	result[j] = '\0';
	return (result);
}

char	*ft_strdupi(char *original, int *index, int size)
{
	char	*copy;
	int		i;

	if (*index != 0 && original[*index] == '|')
		*index = *index + 1;
	while (is_whitespace(original[*index]))
	{
		*index = *index + 1;
		--size;
	}
	copy = malloc((size + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = original[*index];
		*index = *index + 1;
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	free_double_char(char **to_free)
{
	int	i;

	i = 0;
	if (!to_free)
		return ;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}
