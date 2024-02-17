/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/13 13:38:36 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_first_error
{
	ENEWLINE,
	R1Q,
	R2Q,
	L1Q,
	L2Q,
	L3Q,
}				t_first_error;


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
	INPUT_ERROR,
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

struct				s_cmds_piped
{
	t_bool			valid;
	int (*pipes)[2];
	int				count;
	struct s_cmd	**cmds;
};

typedef int		(*t_builtin_f)(int, char **, char **);

int				char_is_quote(char c);
int				char_is_whitespace(char c);
int				char_is_alphanum(char c);
int				char_is_parasit(char c);
int				char_is_delimiter(char c);

char			**ft_split_path(char const *s, char c);
char			*ft_strdup(const char *s);
char			*ft_strdupi(char *original, int *index, int size);
int				ft_strcmp(char *modele, char *compared);
int				ft_strbackslashn(char *s);
char			*ft_strdup_env(const char *s, char *cut);
void			ft_str_append(char **begin, int *j, char *end);
char			*ft_strcatslash(char *begin, char *end);
char			*ft_itoa(int i);

void			increment_both(int *counter, int *index);
char			**scrap_input(int command_number, char *usr_input);
void			free_all(char **commands);
void			dup_and_get_next(char **copy, int *i, char **paste, int *j);
void			skip_undesired(char *command, int *i, int *reset, int *c);
int				check_for_empty(char *buffer, int i);

char			*get_the_next_arg(char *command, int *i);
int				get_command_number(char *buffer);
char			*get_the_program(char *command, int *i);
char			**get_the_arguments(char *command, int *i, char *program_name);
char			**get_splitted_path(char **envp);
int				get_command_length(char *buffer, int i);
char			*get_the_prog_name(char *command, int *i);
int				get_the_next_arg_length(char *command, int i);
char			*get_env(char **envp, char *extracted);

int				find_next_quote(char *buffer, int *i, char quote_type, int x);
char			*find_executable_path(char *program_to_find, char **paths);

int				command_disection(char *command, t_com *comm);
void			skip_to_the_next_word(char *s, int *i);
void			skip_the_word(char *s, int *i);
void			skip_the_next_word(char *s, int *i);

int				has_heredoc(char *command, t_com *comm);
void			has_input(char *command, t_com *comm, int last_index_hd, int i);
void			has_output(char *command, t_com *comm);

char			*exit_to_text(t_exit exit);
char			*entry_to_text(t_entry entry);

int				create_the_com_table(char *usr_input, char **commands,
					int command_number);
//int				check_for_error_hd(char *command, int i, t_com *comm, int c);
int				check_for_error_output(char *command, int i);
char			check_for_next_char(char *command, int i);
void			look_for_heredoc(char *command, int *i, t_com *comm);
int				get_heredocs(char *command, int *i, t_com *comm, int *j);
int				manage_errored_output(char *command, int *i, t_com *comm, char ch);
void			manage_bracketed_input(char *command, int *i, t_com *comm, char ch);
void			manage_empty_input(int *i, t_com *comm);

size_t			ft_dt_len(void **s);
void			free_dt(void **s);
char			**dup_char_dt(char **src);
void			init_rand(void);
char			**compute_path(void);
void			resolve_dum_heredoc(char **here_docs, t_bool is_heredoc);
char			*resolve_path_to_abs(char *exec);
void			*deinit_thgg(t_main *thgg);
void			m_close(int fd);
int				b_pwd(int argc, char **argv, char **envp);
int				b_exit(int argc, char **argv, char **envp);
int				b_env(int argc, char **argv, char **envp);
int				b_echo(int count, char **args, char **envp);
int				forks(t_main *data);
t_u8			is_builtin(char *exec);
int				manage_shit(char *command, int i, char ch);
void	free_double_char(char **to_free);
int	first_command_valid(char *buffer);

#endif