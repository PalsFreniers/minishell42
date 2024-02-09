#include "minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_strbackslashn(char *s)
{
	int i;
	i = 0;
	while (s[i] != '\n')
		i++;
	return(i);
}

char	*ft_strdup(const char *s)
{
	int		l;
	int		i;
	char	*k;

	i = 0;
	l = ft_strlen((char *)s);
	k = malloc((l + 1) * (sizeof(const char)));
	if (k == NULL)
		return (NULL);
	while (s[i])
	{
		k[i] = s[i];
		i++;
	}
	k[i] = '\0';
	return (k);
}

char	*ft_strdupi(char *original, int *index, int size)
{
	char	*copy;
	int		i;

	if (original[*index] == '|')
		*index = *index + 1;
	while (original[*index] == ' ')
	{
		*index = *index + 1;
		--size;
	}
	if (size < 1)
		return (NULL);
	copy = malloc((size + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = original[*index];
		*index = *index + 1;
		i++;
	}
	copy[i] = '\0';
	//printf("sortidupi:'%s'\n", copy);
	return (copy);
}

int	ft_strcmp(char *modele, char *compared)
{
	int	i;

	i = 0;
	while (modele[i])
	{
		if (compared[i] != modele[i])
			return (-1);
		++i;
	}
	if (compared[i])
		return (-1);
	return (1);
}

char	*ft_strcatslash(char *begin, char *end)
{
	int		i;
	int		j;
	int		l;
	char	*result;

	l = ft_strlen(begin) + ft_strlen(end);
	result = malloc((l + 2) * sizeof(char));
	i = 0;
	j = 0;
	while (begin[i])
		result[j++] = begin[i++];
	i = 0;
	result[j++] = '/';
	while (end[i])
		result[j++] = end[i++];
	result[j] = 0;
	return (result);
}
