#include "minishell.h"

int	ft_find_begin(char *modele, char *compared)
{
	int	i;

	i = 0;
	while (modele[i])
	{
		if (compared[i] == modele[i])
			++i;
		else
			return (-1);
	}
	return (1);
}

char	*get_paths(char **envp)
{
	int		i;
	int		l;
	char	*paths;

	i = 0;
	l = 0;
	while (envp[i])
	{
		if (ft_find_begin("PATH=", envp[i]) == 1)
			break ;
		++i;
	}
	if (!envp[i])
	{
		//printf("Error, finding PATH env");
		return (NULL);
	}
	paths = ft_strdup(envp[i]);
	return (paths);
}

char	**get_splitted_path(char **envp)
{
	char	*paths;
	char	**splitted_paths;

	paths = get_paths(envp);
	if (!paths)
	{
		//printf("Error, no paths envp\n");
		return (NULL);
	}
	splitted_paths = ft_split(paths, ':');
	free(paths);
	return (splitted_paths);
}

char	*find_executable_path(char *program_to_find, char **paths)
{
	int		i;
	char	*path_to_test;

	i = 0;
	while (paths[i])
	{
		path_to_test = ft_strcatslash(paths[i], program_to_find);
		if (access(path_to_test, X_OK) == 0)
			return (path_to_test);
		else
		{
			free(path_to_test);
			++i;
		}
	}
	//printf("Error, executable path not found\n");
	return (NULL);
}
