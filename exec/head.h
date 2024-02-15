/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:04:06 by tdelage           #+#    #+#             */
/*   Updated: 2024/02/12 15:15:08 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H


typedef enum e_outkind
{
	APPEND,
	OVERWRITE,
	FILE_ERROR,
}				t_outkind;

typedef enum e_entry
{
	ENTRY_HEREDOC,
	ENTRY_INPUT,
	ENTRY_PIPE,
	NO_ENTRY,
	HD_ERROR,
}				t_entry;

typedef enum e_exit
{
	EXIT_OUTPUT,
	EXIT_PIPE,
	EXIT_STDOUT,
}				t_exit;

typedef struct s_command
{
	int			command_id;
	char		*command;
	char		*program;
	char		**arguments;
	int			has_heredoc;
	char		**here_doc_delimiter;
	bool		has_input;
	char		*input;
	int			fd_input;
	bool		has_output;
	char		*output;
	int			fd_output;
	char		*error;
	t_outkind	outkind;
	t_entry		entry;
	t_exit		exit;
}				t_com;

typedef struct s_main
{
	char		*usr_input;
	char		**envp;
	char		**paths;
	int			command_c;
	char		**commands;
	t_com		**commands_data;
}				t_main;

struct			s_cmd
{
	char		*exec;
	char		**args;
	char		**env;
	int			infd;
	int			outfd;
};

typedef int		(*t_builtin_f)(int, char **, char **);

size_t			ft_dt_len(void **s);
void			free_dt(void **s);
char			**dup_char_dt(char **src);
void			init_rand(void);
char			**compute_path(void);
void			resolve_dum_heredoc(char **here_docs, t_bool is_heredoc);
char			*resolve_path_to_abs(char *exec);
void			*deinit_thgg(t_main *thgg);
void			m_close(int fd);

#endif // HEAD_H
