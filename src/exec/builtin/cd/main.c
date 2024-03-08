/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:14:09 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/08 10:56:02 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

char	*get_env_value_view(char *name, char **envp);

int	b_cd(int argc, char **argv, char **envp)
{
	char	*path;

	if (argc == 1)
	{
		path = get_env_value_view("HOME", envp);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (argc > 2)
	{
		ft_fprintf(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
	{
		ft_fprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (0);
}
