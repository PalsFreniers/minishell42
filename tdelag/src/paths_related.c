/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_related.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 11:10:02 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_begin(char *modele, char *compared)
{
	int	i;

	i = 0;
	while (modele[i])
	{
		if (compared[i] == modele[i])
			++i;
		else
			return (-1);
	}
	if (compared[i] && compared[i] == '=')
		return (1);
	return (-1);
}

char	*get_env(char **envp, char *extracted)
{
	int		i;
	char	*env_var;

	i = 0;
	while (envp[i])
	{
		if (ft_find_begin(extracted, envp[i]) == 1)
			break ;
		++i;
	}
	if (!envp[i])
		return (NULL);
	env_var = ft_strdup_env(envp[i], extracted, 0, 0);
	return (env_var);
}

char	**get_splitted_path(char **envp)
{
	char	*paths;
	char	**splitted_paths;

	paths = get_env(envp, "PATH");
	if (!paths)
		return (NULL);
	splitted_paths = ft_split_path(paths, ':');
	free(paths);
	return (splitted_paths);
}
