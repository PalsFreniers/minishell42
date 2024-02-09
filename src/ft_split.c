#include "minishell.h"

static int	count_split(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static char	*creation_of_char_star(char const *s, char c, int i)
{
	int		count;
	char	*r;

	count = 0;
	while (s[i] != c && s[i])
	{
		count++;
		i++;
	}
	r = malloc((count + 1) * sizeof(char));
	return (r);
}

static void	caseofexit(char **r, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(r[i]);
		i++;
	}
	free(r);
	return ;
}

static char	**creation_of_char_star_star(char const *s, char c, char **r)
{
	int	i;
	int	j;
	int	k;

	i = 5;
	j = 0;
	while (s[i])
	{
		k = 0;
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			r[j] = creation_of_char_star(s, c, i);
			if (!r[j])
			{
				(caseofexit(r, j));
				return (NULL);
			}
			while (s[i] != c && s[i])
				r[j][k++] = s[i++];
			r[j][k] = 0;
			j++;
		}
	}
	r[j] = NULL;
	return (r);
}

char	**ft_split_path(char const *s, char c)
{
	char	**r;

	if (s == NULL)
		return (NULL);
	r = malloc((count_split(s, c) + 1) * sizeof(char *));
	if (!r)
		return (NULL);
	r = creation_of_char_star_star(s, c, r);
	return (r);
}
