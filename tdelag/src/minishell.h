/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:06:25 by dosokin           #+#    #+#             */
/*   Updated: 2024/03/05 16:54:29 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
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

typedef struct s_dup_data
{
	int				l;
	char			*result;
	bool			multiple_word;
	bool			reset;
}					t_dup_data;

struct				s_mainloop
{
	int				cont;
	int				last;
};

typedef struct s_length_exp
{
	int				i;
	int				l;
	bool			is_double_quote;
	int				last;
}					t_length_exp;

typedef enum e_exp_type
{
	EQUAL,
	PLUS,
}					t_exp_type;

typedef struct s_exp_actions
{
	t_exp_type		type;
	char			*var_name;
	char			*var_value;
}					t_exp;

typedef struct s_global_expansion
{
	int				exp_count;
	t_exp			**exps;
}					t_big_exp;

typedef enum e_first_error
{
	ENEWLINE,
	R1Q,
	R2Q,
	L1Q,
	L2Q,
	L3Q,
}					t_first_error;

typedef enum e_outkind
{
	APPEND,
	OVERWRITE,
	FILE_ERROR,
}					t_outkind;

typedef enum e_entry
{
	ENTRY_HEREDOC,
	ENTRY_INPUT,
	ENTRY_PIPE,
	NO_ENTRY,
	HD_ERROR,
	INPUT_ERROR,
}					t_entry;

typedef enum e_exit
{
	EXIT_OUTPUT,
	EXIT_PIPE,
	EXIT_STDOUT,
}					t_exit;

typedef struct s_data_expand
{
	char			*expanded;
	char			*test_env_name;
	bool			is_double_quote;
	int				last;
	int				i;
	int				j;
}					t_data_e;

typedef struct s_command
{
	int				command_id;
	char			*command;
	bool			has_program;
	char			*program;
	char			**arguments;
	int				has_heredoc;
	char			**here_doc_delimiter;
	bool			expand_hd;
	bool			has_input;
	char			*input;
	int				fd_input;
	bool			has_output;
	char			*output;
	int				fd_output;
	char			*error;
	t_outkind		outkind;
	t_entry			entry;
	t_exit			exit;
}					t_com;

typedef struct s_main
{
	char			*usr_input;
	char			**envp;
	char			**paths;
	int				command_c;
	char			**commands;
	t_com			**commands_data;
}					t_main;

struct				s_cmd
{
	char			*exec;
	char			**args;
	char			**env;
	int				infd;
	int				outfd;
};

struct				s_cmds_piped
{
	t_bool			valid;
	int	(*pipes)[2];
	int				count;
	struct s_cmd	**cmds;
};

struct				s_reset_vec
{
	int				c_stdin;
	int				c_stdout;
};

extern int			g_signum;

typedef int			(*t_builtin_f)(int, char **, char **);

bool				is_quote(char c);
bool				is_whitespace(char c);
bool				is_alphanum(char c);
bool				is_parasit(char c);
bool				is_delimiter(char c);
char				**ft_split_path(char const *s, char c);
char				*ft_strdup(const char *s);
char				*ft_strdupi(char *original, int *index, int size);
char				*ft_strdup_env(const char *s, char *cut, int i, int j);
void				ft_str_append(char **begin, int *j, char *end);
void				increment_both(int *counter, int *index);
char				**scrap_input(int command_number, char *usr_input);
void				dup_and_get_next(char **copy, int *i, char **paste, int *j);
void				skip_undesired(char *command, int *i, int *reset, int *c);
int					check_for_empty(char *buffer, int i);
int					gtna_quote_case(char *command, int *i, char *type_quote);
void				skip_ending_quotes(char *command, int *i, int length);
void				skip_in_outs_hds(char *command, int *i);
int					get_command_number(char *buffer);
char				**get_the_arguments(char *command, int *i,
						char *program_name);
char				**get_splitted_path(char **envp);
int					get_command_length(char *buffer, int i);
char				*get_env(char **envp, char *extracted);
int					find_next_quote(char *buffer, int *i, char quote_type,
						int x);
int					command_disection(char *command, t_com *comm);
void				skip_to_the_next_word(char *s, int *i);
void				skip_the_word(char *s, int *i);
void				skip_the_next_word(char *s, int *i);
int					has_heredoc(char *command, t_com *comm);
void				has_input(char *command, t_com *comm, int last_index_hd,
						int i);
void				has_output(char *command, t_com *comm);
bool				is_numeric(char c);
bool				first_character_env_invalid(char c);
bool				ft_strcmp(char *modele, char *compared);
char				*exit_to_text(t_exit exit);
char				*entry_to_text(t_entry entry);

int					create_the_com_table(char *usr_input, char **commands,
						int command_number);
int					check_for_error_output(char *command, int i);
int					create_the_com_table(char *usr_input, char **commands,
						int command_number);
char				check_for_next_char(char *command, int i);
void				look_for_heredoc(char *command, int *i, t_com *comm);
int					get_heredocs(char *command, int *i, t_com *comm, int *j);
size_t				ft_dt_len(void **s);
void				free_dt(void **s);
char				**dup_char_dt(char **src);
void				init_rand(void);
char				**compute_path(void);
void				resolve_dum_heredoc(char **here_docs, t_bool is_heredoc);
char				*resolve_path_to_abs(char *exec);
void				m_close(int fd);
int					b_pwd(int argc, char **argv, char **envp);
int					b_exit(int argc, char **argv, char **envp);
int					b_env(int argc, char **argv, char **envp);
int					b_cd(int argc, char **argv, char **envp);
int					b_echo(int count, char **args, char **envp);
int					b_unset(int count, char **args, char **envp);
int					forks(t_main *data, int last);
t_u8				is_builtin(char *exec);
int					manage_shit(char *command, int i, char ch);
void				free_double_char(char **to_free);
int					first_command_valid(char *buffer);
void				free_double_char(char **to_free);
int					first_command_valid(char *buffer);
void				error_exit_hd(char *input, int i);
int					check_next_char_errority(char *input, int i);
int					check_character(char *buffer, int *j, bool *empty,
						bool *parasit);
int					check_usr_input_for_errors(char *input);
int					is_usr_input_blank(char *usr_input);
void				deinit_cd_first(t_com *comm);
void				deinit_commands_data(t_com **command_data);
void				*deinit_thgg(t_main *thgg);
void				deinit_cd_second(t_com *comm);
int					init_cd_first(t_com *command, char **commands, int i,
						int command_c);
t_com				**init_command_data(int command_c, char **commands);
t_main				*check_commands_integrity(t_main *thgg);
t_main				*init_thgg(char **envp, char *o_usr_input);
int					primary_exception_cancel(char *usr_input, int *i, int *l,
						int last);
void				single_quote_expansion(char *usr_input, int *i, int *l);
void				exp_single_quote(char *usr_input, int *i, char *expanded,
						int *j);
char				*get_the_test_env(char *usr_input, int *i);
void				add_env_var(char *expanded, int *j, char *test_env_name,
						char **envp);
char				*create_expanded(int l);
void				error_exit_hd(char *input, int i);
int					ft_strlen_char_ss(char **s);
char				**ft_strdup_char_star(char **to_dup);
t_big_exp			*get_big_exp(int argc, char **argv);
int					expansion_char_is_dollar(char *usr_input, int *i,
						t_data_e *exp, int *j);
int					get_length_expanded(char *usr_input, char **envp, int last);
void				get_length_dollar(char *usr_input, char **envp,
						t_length_exp *data);
char				*expansion(char *usr_input, char **envp, int last);
void				free_big_exp(t_big_exp *big_exp);
int					resolve_out(t_com *self, int (*pipes)[2], int id);
int					resolve_entry(t_com *self, int (*pipes)[2],
						struct s_mainloop data, char **env);
char				*get_the_next_arg(char *command, int *i, bool *has_program);
struct s_mainloop	print_export(char **envp);
int					b_export(int argc, char **argv, char **envp);
t_bool				is_env(char *arg, char **envp);
void				remove_one(char *argument, char ***envp);
char				*get_env_value_view(char *name, char **envp);
void				create_env(char *name, char *value, char ***envp);
char				**sort_env(char **envp);
struct s_mainloop	print_export(char **envp);
struct s_mainloop	sb_exit(t_com *command);
struct s_mainloop	sb_unset(t_com *command, char ***envp);
struct s_mainloop	sb_export(char ***envp, t_com *command);
struct s_mainloop	sb_cd(int argc, t_com *command, char ***envp);
struct s_mainloop	solo_b_in(t_com *command, char ***envp, int last);
void				catch_int(int sn);
struct s_mainloop	give_the_prompt(char ***envp, int last);
char				*get_the_var_value(char *s, int *i, t_exp_type *type);
int					check_for_exp_c(int argc, char **argv);
char				*get_the_var_value(char *s, int *i, t_exp_type *type);
bool				is_exp_struct(char *s);
char				*get_the_exp_name(char *command, int *i);
char				*ft_find_path(char *exec, char **paths);
void				free_cmds(struct s_cmds_piped piped, int skip);
void				free_cmd(struct s_cmd *cmd);
void				generate_fork_data(struct s_cmds_piped *self, t_main *data,
						int last);
t_u8				is_builtin(char *exec);
t_builtin_f			get_builtin(char *exec);
void				exec(t_main *data, struct s_cmds_piped cmds, int id,
						int *pids);
void				close_all_pipes(int (*pipes)[2], int count);
int					make_here_doc_file(char *limiter, char **env,
						struct s_mainloop data);
void				catch_int(int sn);
void				catch_int2(int sn);

#endif
