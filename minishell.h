/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/02/12 11:47:44 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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

int				char_is_quote(char c);
int				char_is_whitespace(char c);
int				char_is_alphanum(char c);
int				char_is_parasit(char c);
int				char_is_delimiter(char c);

char			**ft_split_path(char const *s, char c);
int				ft_strlen(char *s);
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
int				get_the_next_arg_length(char *command, int *i);
char			*get_env(char **envp, char *extracted);

int				find_next_quote(char *buffer, int *i, char quote_type);
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
int				check_for_error_hd(char *command, int i, t_com *comm, int c);
int             check_for_error_output(char *command, int i);
char            check_for_next_char(char *command, int i);
void			look_for_heredoc(char *command, int *i, t_com *comm);
int				get_heredocs(char *command, int *i, t_com *comm, int *j);
int    			manage_errored_output(char *command, int *i, int *c, t_com *comm);
void    		manage_bracketed_input(char *command, int *i, int *c, t_com *comm);
void    		manage_empty_input(int *i, t_com *comm);

#endif
