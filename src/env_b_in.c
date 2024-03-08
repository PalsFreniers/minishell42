/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_b_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:29:52 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/08 01:01:20 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_env(char *arg, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(arg, envp[i], ft_strlen(arg)) == 0
			&& envp[i][ft_strlen(arg)] == '=')
			return (TRUE);
	}
	return (FALSE);
}

void	remove_one(char *argument, char ***envp)
{
	char	**tmp;
	int		j;
	int		k;

	if (is_env(argument, *envp))
	{
		tmp = malloc(sizeof(char *) * (ft_dt_len((void **)*envp)));
		j = -1;
		k = -1;
		while ((*envp)[++j])
		{
			if (ft_strncmp(argument, (*envp)[j], ft_strlen(argument)) != 0
				|| (ft_strncmp(argument, (*envp)[j], ft_strlen(argument)) == 0
					&& (*envp)[j][ft_strlen(argument)] != '='))
			{
				tmp[++k] = (*envp)[j];
			}
			else
				free((*envp)[j]);
		}
		tmp[++k] = NULL;
		free(*envp);
		*envp = tmp;
	}
}

char	*get_env_value_view(char *name, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(name, envp[i], ft_strlen(name)) == 0)
			return (envp[i] + ft_strlen(name) + 1);
	return (NULL);
}

void	create_env(char *name, char *value, char ***envp)
{
	char	**tmp;
	char	*tmp2;
	int		i;

	tmp = malloc(sizeof(char *) * (ft_dt_len((void **)*envp) + 2));
	if (!tmp)
		return ;
	i = -1;
	while ((*envp)[++i])
		tmp[i] = (*envp)[i];
	tmp2 = ft_strjoin(name, "=");
	tmp[i] = ft_strjoin(tmp2, value);
	free(tmp2);
	tmp[i + 1] = NULL;
	free(*envp);
	*envp = tmp;
}

char	**sort_env(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	envp = dup_char_dt(envp);
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}
