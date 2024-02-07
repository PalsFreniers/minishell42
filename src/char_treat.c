#include "minishell.h"

int	char_is_alphanum(char c)
{
	if (c == '|')
		return (-1);
	else if (c == '\'')
		return (-1);
	else if (c == '\"')
		return (-1);
	else if (c >= 32 && c < 127)
		return (1);
	else
		return (-1);
}

int	char_is_whitespace(char c)
{
	if (c == '\r' || c == ' ' || c == '\t')
		return (1);
	if (c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (-1);
}

int	find_next_quote(char *buffer, int *i, char quote_type)
{
	*i = *i + 1;
	while (buffer[*i] && buffer[*i] != quote_type)
		*i = *i + 1;
	if (!buffer[*i])
	{
		printf("unclosed quotes\n");
		return (-1);
	}
	*i = *i + 1;
	return (1);
}

int	char_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (-1);
}