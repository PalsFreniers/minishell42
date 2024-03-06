/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:19:04 by tdelage           #+#    #+#             */
/*   Updated: 2024/03/04 21:20:25 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define MAX_FILE_TRIES 100

void	ft_file_name_rand(char file[20])
{
	char	*str;
	int		len;
	int		i;

	str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	len = ft_strlen(str);
	i = 4;
	ft_memcpy(file, "/tmp/", 5);
	while (++i < 20)
		file[i] = str[ft_rand(0, len - 1)];
}

void	generate_non_existing_file(char *file)
{
	int	i;

	i = 0;
	ft_file_name_rand(file);
	while (++i < MAX_FILE_TRIES && access(file, F_OK) == 0)
		ft_file_name_rand(file);
}

void	write_heredoc(int fd, char *limiter, struct s_mainloop data,
		char **envp)
{
	char	*c;
	char	*tmp;

	while (1)
	{
		if (g_signum == SIGINT)
			break ;
		c = readline("> ");
		if (!c)
			continue ;
		c[ft_strlenc(c, '\n') + 1] = 0;
		if (ft_strequ(c, limiter))
		{
			free(c);
			break ;
		}
		if (data.cont)
		{
			tmp = c;
			c = expansion(tmp, envp, data.last);
		}
		ft_fprintf(fd, "%s\n", c);
		free(c);
	}
}

int	make_here_doc_file(char *limiter, char **env, struct s_mainloop data)
{
	int			fd;
	static char	file[21] = {0};

	generate_non_existing_file(file);
	file[20] = 0;
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (fd);
	write_heredoc(fd, limiter, data, env);
	m_close(fd);
	fd = open(file, O_RDONLY, 0644);
	if (fd == -1)
		return (fd);
	unlink(file);
	return (fd);
}
