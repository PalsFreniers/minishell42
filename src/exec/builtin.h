/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:49:19 by tdelage           #+#    #+#             */
/*   Updated: 2024/02/12 12:50:51 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int	b_pwd(int argc, char **argv, char **envp);
int	b_exit(int argc, char **argv, char **envp);
int	b_env(int argc, char **argv, char **envp);
int	b_echo(int count, char **args, char **envp);

#endif // BUILTIN_H
