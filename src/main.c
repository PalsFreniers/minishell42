#include "minishell.h"

// int	launch_task(char *command, int *pipefd, char **paths)
// {
// 	char	*program_name;
// 	char	**arguments;
// 	char	*executable_path;
// 	int		id2;
// 	int		i;

// 	(void)pipefd;
// 	arguments = NULL;
// 	id2 = 0;
// 	i = 0;
// 	command_disection(command, &program_name, &arguments);
// 	if (program_name)
// 	{
// 		// //printf("program = %s\n", program_name);
// 		executable_path = find_executable_path(program_name, paths);
// 		// //printf("path exec=%s\n", command);
// 		id2 = fork();
// 		if (id2 == 0)
// 		{
// 			execve((const char *)executable_path, arguments, NULL);
// 			//printf("Execve failed\n");
// 			return (-1);
// 		}
// 		free(program_name);
// 		while (paths[i])
// 			free(paths[i++]);
// 		free(paths);
// 		free(executable_path);
// 		waitpid(id2, NULL, 0);
// 	}
// 	i = 0;
// 	if (arguments)
// 	{
// 		while (arguments[i])
// 		{
// 			// //printf("argument #%d: %s\n", i, arguments[i]);
// 			free(arguments[i]);
// 			++i;
// 		}
// 		free(arguments);
// 	}
// 	return (1);
// }

// int	launch_programms(char **commands, int command_number, char **paths, int *id)
// {
// 	int	pipefd[2];
// 	int	n;

// 	n = 0;
// 	if (pipe(pipefd) == -1)
// 		return (-1);
// 	while (n < command_number)
// 	{
// 		// //printf("command: %s\n", commands[n]);
// 		*id = fork();
// 		if (*id == 0)
// 		{
// 			launch_task(commands[n], pipefd, paths);
// 			// return (-1);
// 			// break ;
// 			close(pipefd[0]);
// 			close(pipefd[1]);
// 			free_all(commands);
// 			return (-1);
// 		}
// 		else
// 			waitpid(*id, NULL, 0);
// 		++n;
// 	}
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	return (1);
// }

void	free_double_char(char **to_free)
{
	int i;

	i = 0;
	if (!to_free)
		return ;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

void	deinit_commands_data(t_com **command_data)
{
	int	i;
	int	j;

	i = 0;
	while (command_data[i])
	{
		j = 0;
		free(command_data[i]->program);
		while (command_data[i]->arguments[j])
		{
			free(command_data[i]->arguments[j]);
			j++;
		}
		free(command_data[i]->arguments);
		j = 0;
		if (command_data[i]->has_heredoc)
		{
			while (command_data[i]->here_doc_delimiter[j])
			{
				free(command_data[i]->here_doc_delimiter[j]);
				j++;
			}
			free(command_data[i]->here_doc_delimiter);
		}
		if (command_data[i]->has_input)
			free(command_data[i]->input);
		if (command_data[i]->has_output)
			free(command_data[i]->output);
		free(command_data[i]);
		i++;
	}
	free(command_data);
}

void	*deinit_thgg(t_main *thgg)
{
	if (thgg->usr_input)
		free(thgg->usr_input);
	if (thgg->paths)
		free_double_char(thgg->paths);
	if (thgg->commands)
		free_double_char(thgg->commands);
	if (thgg->commands_data)
		deinit_commands_data(thgg->commands_data);
	free(thgg);
	return (NULL);
}

// char **get_programms(int command_c, char **commands)
// {
// 	char **programs;
// 	int	j;

// 	programs = malloc((command_c + 1) * sizeof(char *));
// 	if (!programs)
// 		return (NULL);
// 	j = 0;
// 	while (j < command_c)
// 	{
// 		program[j] = get_the_program(commands[j])
// 	}
// }

t_com	**init_command_data(int command_c, char **commands)
{
	t_com **commands_data;
	t_com *command;
	int	i;

	commands_data = malloc((command_c + 1) * sizeof(t_com*));
	i = 0;
	while (i < command_c)
	{
		commands_data[i] = malloc(sizeof(t_com));
		command = commands_data[i];
		command->command = commands[i];
		command->error = NULL;
		if (command_disection(commands[i], command) == -1)
			return (NULL);
		i++;
	}
	commands_data[i] = NULL;
	return (commands_data);
}

t_main	*init_thgg(char **envp, char *o_usr_input)
{
	t_main *thgg;

	thgg = malloc(sizeof(t_main));
	thgg->commands = NULL;
	thgg->commands_data = NULL;
	thgg->id = 1;
	thgg->usr_input = ft_strdup(o_usr_input);
	free(o_usr_input);
	thgg->envp = envp;
	thgg->paths = get_splitted_path(envp);
	thgg->command_c = get_command_number(thgg->usr_input);
	if (thgg->command_c < 1)
		return (deinit_thgg(thgg));
	thgg->commands = scrap_input(thgg->command_c, thgg->usr_input);
	if (!thgg->commands)
		return (deinit_thgg(thgg));
	thgg->commands_data = init_command_data(thgg->command_c, thgg->commands);
	if (!thgg->commands_data)
		return (deinit_thgg(thgg));
	return (thgg);
}

char	*ft_strdup_and_add_char(char *s, char c)
{
	char *result;
	int i;

	i = 0;
	result = malloc((ft_strlen(s) + 2) * sizeof(char));
	if (!result)
		return (NULL);
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = c;
	i++;
	result[i] = '\0';
	return (result);
}



char *get_test_env_name(char *test_env_name, char current_char)
{
	char *new_test_name;

	if (!test_env_name)
	{
		new_test_name = malloc(2 * sizeof(char));
		new_test_name[0] = current_char;
		new_test_name[1] = '\0';
		return (new_test_name);
	}
	new_test_name = ft_strdup_and_add_char(test_env_name, current_char);
	free(test_env_name);
	test_env_name = NULL;
	return (new_test_name);
}

int	get_length_expanded(char *usr_input, char **envp)
{
	int i;
	int j;
	int l;
	char *env_var;
	char *test_env_name;
	bool is_double_quote;

	l = 0;
	i = 0;
	is_double_quote = false;
	while (usr_input[i])
	{
		if (usr_input[i] == '\'' && !is_double_quote)
		{
			j = i;
			find_next_quote(usr_input, &i, '\'');
			l += i - j;
		}
		else if (usr_input[i] == '\"')
		{
			is_double_quote = !is_double_quote;
			++l;
			++i;
		}
		else if (usr_input[i] == '$')
		{
			if (char_is_whitespace(usr_input[i + 1]))
			{
				l += 2;
				i++;
				continue ;
			}
			// if (usr_input[i + 1] == '?')
			// {
			// 	test_env_name = NULL;
			// 	env_var = ft_itoa(getpid());
			// 	i += 2;
			// }
			else
			{
				j = ++i;
				test_env_name = NULL;
				while(usr_input[i] && !(char_is_quote(usr_input[i])) && !(char_is_whitespace(usr_input[i])) && !(char_is_parasit(usr_input[i])) && !char_is_delimiter(usr_input[i]))
					i++;
				test_env_name = ft_strdupi(usr_input, &j, i - j);
				env_var = get_env(envp, test_env_name);
			}
			if (env_var)
			{
				l += ft_strlen(env_var);
				free(env_var);
				if (test_env_name)
					free(test_env_name);
				continue ;
			}
			if (test_env_name)
				free(test_env_name);
		}
		else
		{
			++l;
			++i;
		}
	}
	return (l);
}

char	*get_expanded(char *usr_input, char **envp, int expansion_l)
{
	char *expanded;
	char *env_var;
	char *test_env_name;
	bool is_double_quote;
	int i;
	int	j;
	int k;

	expanded = malloc((expansion_l + 1) * sizeof(char));
	i = 0;
	while (i <= expansion_l)
		expanded[i++] = '\0';
	i = 0;
	j = 0;
	while (usr_input[i])
	{
		if (usr_input[i] == '\'' && !is_double_quote)
		{
			while (usr_input[i] && usr_input[i] != '\'')
				expanded[j++] = usr_input[i++];
			expanded[j++] = usr_input[i++];
		}
		else if (usr_input[i] == '\"')
		{
			is_double_quote = !is_double_quote;
			expanded[j++] = usr_input[i++];
		}
		else if (usr_input[i] == '$')
		{
			if (char_is_whitespace(usr_input[i + 1]))
			{
				expanded[j++] = usr_input[i++];
				continue ;
			}
			// if (usr_input[i + 1] == '$')
			// {
			// 	test_env_name = NULL;
			// 	env_var = ft_itoa(getpid());
			// 	i += 2;
			// }
			else
			{
				k = ++i;
				test_env_name = NULL;
				while(usr_input[i] && !(char_is_quote(usr_input[i])) && !(char_is_whitespace(usr_input[i])) && !(char_is_parasit(usr_input[i])) && !char_is_delimiter(usr_input[i]))
					i++;
				test_env_name = ft_strdupi(usr_input, &k, i - k);
				env_var = get_env(envp, test_env_name);

			}
			if (env_var)
			{
				ft_str_append(&expanded, &j, env_var);
				free(env_var);
				if (test_env_name)
					free(test_env_name);
				continue ;
			}
			if (test_env_name)
				free(test_env_name);
		}
		else
			expanded[j++] = usr_input[i++];
	}
	printf("%s\n", expanded);
	return (expanded);
}

char *expansion(char *usr_input, char **envp)
{
	char *expanded_input;
	int expanded_l;

	expanded_l = get_length_expanded(usr_input, envp);
	if (expanded_l == ft_strlen(usr_input))
		return (usr_input);
	expanded_input = get_expanded(usr_input, envp, expanded_l);
	free(usr_input);
	return (expanded_input);
}

// char *primary_parse(char *usr_input, char **envp)
// {
// 	// char *expanded_input;

// 	// expanded_input = expansion(usr_input, envp);
// 	// return (expanded_input);
// 	//get_length_expanded(usr_input, envp);
// 	return NULL;
// }

int	give_the_prompt(char **envp)
{
	t_main *thgg;
	char *usr_input;

	usr_input = readline("$> ");
	add_history(usr_input);
	// first_parsed = primary_parse(usr_input, envp);
	usr_input = expansion(usr_input, envp);
	thgg = init_thgg(envp, usr_input);
	if (!thgg)
	{
		//printf("prout\n");
		return (0) ;
	}
	int i;
	int j;
	i = 0;
	while (thgg->commands_data[i])
	{
		j = 0;
		printf("command #%d:'%s'\nprogram:%s\n", i, thgg->commands_data[i]->command, thgg->commands_data[i]->program);
		if (thgg->commands_data[i]->has_input)
			printf("input:%s\n", thgg->commands_data[i]->input);
		if (thgg->commands_data[i]->has_output)
		{
			printf("output:%s\n", thgg->commands_data[i]->output);
			if (thgg->commands_data[i]->outkind == OVERWRITE)
				printf("OVERWRITE\n");
			else
				printf("APPEND\n");
		}
		while (thgg->commands_data[i]->arguments[j])
		{
			printf("arguments #%d:'%s'\n", j, thgg->commands_data[i]->arguments[j]);
			j++;
		}
		j = 0;
		if (thgg->commands_data[i]->has_heredoc)
		{
			while (thgg->commands_data[i]->here_doc_delimiter[j])
			{
				printf("heredoc #%d:'%s'\n", j, thgg->commands_data[i]->here_doc_delimiter[j]);
				j++;
			}
		}
		printf("\n");
		i++;
	}
	// i = 0;
	// while (thgg->paths[i])
	// {
	// 	//printf("path #%d:'%s'\n", i, thgg->paths[i]);
	// 	i++;
	// }
	// if (scrap_input(buffer, &command_number, &commands) == -1)
	// 	commands = NULL;
	// else if (command_number > 0)
	// 	if (launch_programms(commands, command_number, paths, id) == -1)
	// 		return (-1);
	// free_all(commands);
	// if (buffer)
	// 	free(buffer);
	// if (*id == 0)
	// 	return (-1);
	// return (1);
	deinit_thgg(thgg);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (!envp)
	{
		printf("Error, no envp\n");
		return (-1);
	}
	while (1)
		if (give_the_prompt(envp) == -1)
			break ;
	return (0);
}
