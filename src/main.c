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
// 		// printf("program = %s\n", program_name);
// 		executable_path = find_executable_path(program_name, paths);
// 		// printf("path exec=%s\n", command);
// 		id2 = fork();
// 		if (id2 == 0)
// 		{
// 			execve((const char *)executable_path, arguments, NULL);
// 			printf("Execve failed\n");
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
// 			// printf("argument #%d: %s\n", i, arguments[i]);
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
// 		// printf("command: %s\n", commands[n]);
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
		i++;
	}
	free(command_data);
}

void	*deinit_thgg(t_main *thgg)
{
	int i;
	
	i = 0;
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
		if (command_disection(commands[i], command) == -1)
			return (NULL);
		i++;
	}
	commands_data[i] = NULL;
	return (commands_data);
}

t_main	*init_thgg(char **envp, char *usr_input)
{
	t_main *thgg;

	thgg = malloc(sizeof(t_main));
	thgg->id = 1;
	thgg->usr_input = usr_input;
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

int	give_the_prompt(char **envp)
{
	t_main *thgg;
	char *usr_input;

	usr_input = readline("$> ");
	thgg = init_thgg(envp, usr_input);
	if (!thgg)
		return (0) ;
	int i;
	int j;
	i = 0;
	printf("usr:'%s'\nc:%d\n", thgg->usr_input, thgg->command_c);
	while (thgg->commands_data[i])
	{
		j = 0;
		printf("command #%d:'%s'\nprogram:%s\n", i, thgg->commands_data[i]->command, thgg->commands_data[i]->program);
		if (thgg->commands_data[i]->input)
			printf("input:%s\n", thgg->commands_data[i]->input);
		while (thgg->commands_data[i]->arguments[j])
		{
			printf("arguments #%d:'%s'\n", j, thgg->commands_data[i]->arguments[j]);
			j++;
		}
		j = 0;
		if (thgg->commands_data[i]->is_heredoc)
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
	// 	printf("path #%d:'%s'\n", i, thgg->paths[i]);
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
