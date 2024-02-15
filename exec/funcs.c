#include "../minishell.h"

void m_close(int fd) {
        if(fd >= 0)
                close(fd);
}

size_t	ft_dt_len(void **s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	free_dt(void **s)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

char	**dup_char_dt(char **src)
{
	char	**ret;
	size_t	i;

	ret = malloc(sizeof(char *) * (ft_dt_len((void **)src) + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		ret[i] = ft_strdup(src[i]);
		if (ret[i] == NULL)
			free_dt((void **)ret);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	init_rand(void)
{
	int	ps;

	ps = fork();
	if (ps == 0)
		exit(0);
	waitpid(ps, NULL, 0);
	ft_srand(ps);
}

char	**compute_path(void)
{
	char	**ret;
	char	*path;

	path = getenv("PATH");
	if (path == NULL)
	{
		ret = malloc(sizeof(char *));
		if (ret)
			ret[0] = NULL;
		return (ret);
	}
	ret = ft_split(path, ':');
	return (ret);
}
