/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:37:12 by tdelage           #+#    #+#             */
/*   Updated: 2024/02/13 14:49:05 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

int	b_pwd(int argc, char **argv, char **envp)
{
	char	*pwd;
	t_bool	free_pwd;

	(void)argc;
	(void)argv;
	(void)envp;
	free_pwd = FALSE;
	pwd = getenv("PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		free_pwd = TRUE;
	}
	ft_printf("%s\n", pwd);
	if (free_pwd == TRUE)
		free(pwd);
	return (0);
}
