#ifndef MINISHELL_H
#define MINISHELL_H

#include <dirent.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>

typedef enum e_outkind{
    APPEND,
    OVERWRITE,
}   t_outkind;

typedef enum e_entry{
    ENTRY_HEREDOC,
    ENTRY_INPUT,
    ENTRY_PIPE,
}   t_entry;

typedef enum e_exit{
    EXIT_OUTPUT,
    EXIT_PIPE,
}   t_exit;

typedef struct s_command{
    char *command;
    char *program;
    char **arguments;
    int is_heredoc;
    char **here_doc_delimiter;
    bool is_input;
    char *input;
    int fd_input;
    bool is_output;
    char *output;
    int fd_output;
    char *error;
    t_outkind outkind;
    t_entry entry;
    t_exit exit;
}t_com;

typedef struct s_main{
    int id;
    char *usr_input;
    char **envp;
    char **paths;
    int command_c;
    char **commands;
    t_com **commands_data;
}t_main;

int	char_is_quote(char c);
int	char_is_whitespace(char c);
int	char_is_alphanum(char c);
int	char_is_parasit(char c);
int char_is_delimiter(char c);

char	**ft_split_path(char const *s, char c);
int	    ft_strlen(char *s);
char	*ft_strdup(const char *s);
char	*ft_strdupi(char *original, int *index, int size);
int	    ft_strcmp(char *modele, char *compared);
int ft_strbackslashn(char *s);
char	*ft_strdup_env(const char *s, char *cut);
void	ft_str_append(char **begin, int *j, char *end);
char	*ft_strcatslash(char *begin, char *end);
char    *ft_itoa(int i);



void	increment_c_and_i(int *counter, int *index);
char	**scrap_input(int command_number, char *usr_input);
void	free_all(char **commands);

char	*get_the_next_arg(char *command, int *i);
int	    get_command_number(char *buffer);
char    *get_the_program(char *command, int *i);
char	**get_the_arguments(char *command, int *i, char *program_name);
char	**get_splitted_path(char **envp);
int	    get_command_length(char *buffer, int i);
char	*get_the_prog_name(char *command, int *i);
int	get_the_next_arg_length(char *command, int *i);
char	*get_env(char **envp, char *extracted);

int	find_next_quote(char *buffer, int *i, char quote_type);
char	*find_executable_path(char *program_to_find, char **paths);

int	command_disection(char *command, t_com *comm);
void	skip_to_the_next_word(char *s, int *i);
void	skip_the_word(char *s, int *i);
void	skip_the_next_word(char *s, int *i);

void    is_heredoc(char *command, t_com *comm, int *i);
void    is_input(char *command, t_com *comm, int last_index_hd);
void    is_output(char *command, t_com *comm);

#endif