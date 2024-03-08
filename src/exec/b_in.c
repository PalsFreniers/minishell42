/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_in.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:28:33 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/08 11:45:29 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_u8	is_builtin(char *exec)
{
	if (ft_strequ(exec, "echo"))
		return (TRUE);
	if (ft_strequ(exec, "cd"))
		return (TRUE);
	if (ft_strequ(exec, "pwd"))
		return (TRUE);
	if (ft_strequ(exec, "export"))
		return (TRUE);
	if (ft_strequ(exec, "unset"))
		return (TRUE);
	if (ft_strequ(exec, "env"))
		return (TRUE);
	if (ft_strequ(exec, "exit"))
		return (TRUE);
	return (FALSE);
}

t_builtin_f	get_builtin(char *exec)
{
	if (ft_strequ(exec, "echo"))
		return (b_echo);
	if (ft_strequ(exec, "cd"))
		return (b_cd);
	if (ft_strequ(exec, "pwd"))
		return (b_pwd);
	if (ft_strequ(exec, "export"))
		return (b_export);
	if (ft_strequ(exec, "unset"))
		return (b_unset);
	if (ft_strequ(exec, "env"))
		return (b_env);
	return (NULL);
}
