
// char *get_the_current_path(const char *name_of_starture_path,
//	char *name_of_file)
// {
//     char *current_path;
//     int j;
//     int i;

//     i = ft_strlen((char *)name_of_starture_path) + ft_strlen(name_of_file);
//     current_path = malloc((i + 1) * sizeof(char));
//     i = 0;
//     j = 0;
//     while (name_of_starture_path[i])
//         current_path[j++] = name_of_starture_path[i++];
//     i = 0;
//     while (name_of_file[i])
//         current_path[j++] = name_of_file[i++];
//     current_path[j] = 0;
//     return (current_path);
// }

// int    find_executable_path(char *program, const char *name_of_starture_path)
// {
//     DIR *directory;
//     struct dirent *read_dir;
//     char *current_path;

//     directory = opendir(name_of_starture_path);
//     if (directory == NULL)
//     {
//         printf("Error opening directory\n");
//         return (-1);
//     }
//     read_dir = readdir(directory);
//     while (read_dir != NULL)
//     {
//         current_path = get_the_current_path(name_of_starture_path,
//		read_dir->d_name);
//         if (read_dir->d_type == DT_DIR)
//         {
//             if (ft_strcmp(".", read_dir->d_name) == 1)
//                 read_dir = readdir(directory);
//             else if(ft_strcmp("..", read_dir->d_name) == 1)
//                 read_dir = readdir(directory);
//             else
//                 find_executable_path(program, current_path);
//         }
//         else if (ft_strcmp(program, read_dir->d_name) == 1)
//         {
//             printf("path du program: %s\n", current_path);
//             break ;
//         }
//         else
//             read_dir = readdir(directory);
//         free(current_path);
//     }
//     closedir(directory);
//     return (1);
// }


// void    launch_programms(char **commands, int command_number, int n)
// {
//     int id;
//     int pipefd[2];
//     char *buffer;

//     buffer = malloc(1024 * sizeof(char));
//     if (pipe(pipefd) == -1)
//         return ;
//     id = 0;
//     if (n < command_number)
//         launch_programms(commands, command_number, n + 1);
//     id = fork();
//     if (id == 0)
//         launch_task(commands[n - 1], pipefd);
//     else
//     {
//         close(pipefd[1]);
//         read(pipefd[0], buffer, 1024);
//         printf("command : %s\n", buffer);
//         close(pipefd[0]);
//         wait(NULL);
//     }
//     if (buffer)
//         free(buffer);
// }

// char	*get_the_program(char *command, int *i)
// {
// 	char	*program;
// 	int		length;
// 	int		j;

// 	length = 0;
// 	if (command[*i] == '\n')
// 		return (NULL);
// 	while (command[*i] && (char_is_whitespace(command[*i]) == 1))
// 		*i = *i + 1;
// 	j = *i;
// 	while (command[j] && (char_is_whitespace(command[j]) == -1))
// 	{
// 		++length;
// 		++j;
// 	}
// 	if (length == 0)
// 	{
// 		return (NULL);
// 	}
// 	program = malloc((length + 1) * sizeof(char));
// 	j = 0;
// 	while (length > 0)
// 	{
// 		program[j] = command[*i];
// 		*i = *i + 1;
// 		length--;
// 		++j;
// 	}
// 	program[j] = 0;
// 	//*i = *i + 1;
// 	return (program);
// }