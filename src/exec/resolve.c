/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:00:00 by tdelage           #+#    #+#             */
/*   Updated: 2024/02/12 13:21:39 by tdelage          ###   ########.fr       */
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
			ft_printf("%s ", here_docs[i]);
			c = readline("here_doc> ");
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

char	*resolve_path_to_abs(char *exec)
{
	char	*ret;
	char	*pwd;
	char	*tmp;
	t_bool	need_free;

	if (!exec || exec[0] == '/')
		return (exec);
	need_free = FALSE;
	pwd = getenv("PWD");
	if (pwd == NULL)
	{
		pwd = getcwd(NULL, 0);
		need_free = TRUE;
	}
	ret = ft_strjoin(pwd, "/");
	if (need_free)
		free(pwd);
	tmp = ft_strjoin(ret, exec);
	free(ret);
	return (tmp);
}
