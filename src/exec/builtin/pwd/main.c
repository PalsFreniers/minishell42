/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:37:12 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/04 21:13:52 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

int	b_pwd(int argc, char **argv, char **envp)
{
	char	*pwd;

	(void)argc;
	(void)argv;
	(void)envp;
	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}
