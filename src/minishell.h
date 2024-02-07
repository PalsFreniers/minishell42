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

typedef struct s_command{
    char *command;
    char *program;
    char **arguments;
    int is_heredoc;
    char **here_doc_delimiter;
    bool is_input;
    bool multiple_input;
    char *input;
    bool is_output;
    char *output;
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

char	**ft_split(char const *s, char c);
int	ft_strlen(char *s);
char	*ft_strdup(const char *s);
char	*ft_strdupi(char *original, int *index, size_t size);
void	increment_c_and_i(int *counter, int *index);
int	char_is_alphanum(char c);
char	**scrap_input(int command_number, char *usr_input);
void	free_all(char **commands);
int	char_is_quote(char c);
char *get_the_program(char *command, int *i);
char	**get_the_arguments(char *command, int *i, char *program_name);
char	**get_splitted_path(char **envp);
char	*find_executable_path(char *program_to_find, char **paths);
int	ft_strcmp(char *modele, char *compared);
int	command_disection(char *command, t_com *comm);
int	char_is_whitespace(char c);
int	find_next_quote(char *buffer, int *i, char quote_type);
int	get_input_length(char *buffer, int start_index);
char	*ft_strcatslash(char *begin, char *end);
int	get_command_number(char *buffer);
char	*get_the_next_arg(char *command, int *i);
int	char_is_parasit(char c);
int	skip_to_the_next_word(char *s, int i);
int	skip_the_word(char *s, int i);
int    is_heredoc(char *command, t_com *comm, int *i);
void    is_input(char *command, t_com *comm, int *i);

#endif