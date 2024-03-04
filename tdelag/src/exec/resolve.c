/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:00:00 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/04 21:18:27 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	resolve_dum_heredoc(char **here_docs, t_bool is_heredoc)
{
	size_t	num;
	size_t	i;
	char	*c;

	num = ft_dt_len((void **)here_docs) - is_heredoc;
	i = -1;
	while (++i < num)
	{
		while (1)
		{
			if (g_signum == SIGINT)
				break ;
			c = readline("> ");
			if (!c)
				continue ;
			c[ft_strlenc(c, '\n') + 1] = 0;
			if (ft_strequ(c, here_docs[i]))
			{
				free(c);
				break ;
			}
			free(c);
		}
	}
}

int	resolve_heredoc(char **hdd, struct s_mainloop data, t_bool exp, char **env)
{
	int	ret;

	ret = -1;
	resolve_dum_heredoc(hdd, data.cont);
	if (data.cont)
	{
		data.cont = exp;
		ret = make_here_doc_file(hdd[ft_dt_len((void **)hdd) - 1], env, data);
	}
	return (ret);
}

int	resolve_entry(t_com *self, int (*pipes)[2], struct s_mainloop data,
		char **env)
{
	int	ret;
	int	hd;
	int	id;

	id = data.cont;
	if (self->has_heredoc)
	{
		data.cont = self->entry == ENTRY_HEREDOC;
		hd = resolve_heredoc(self->here_doc_delimiter, data, self->expand_hd,
				env);
	}
	if (self->entry == ENTRY_PIPE)
		ret = pipes[id - 1][0];
	else if (self->entry == ENTRY_INPUT)
		ret = self->fd_input;
	else if (self->entry == NO_ENTRY)
		ret = STDIN;
	else if (self->entry == ENTRY_HEREDOC)
		ret = hd;
	else
		ret = -1;
	return (ret);
}

int	resolve_out(t_com *self, int (*pipes)[2], int id)
{
	int	ret;

	if (self->exit == EXIT_PIPE)
		ret = pipes[id][1];
	else if (self->exit == EXIT_OUTPUT)
		ret = self->fd_output;
	else if (self->exit == EXIT_STDOUT)
		ret = STDOUT;
	else
		ret = -1;
	return (ret);
}
