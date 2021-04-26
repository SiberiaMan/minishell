#include "minishell.h"

static size_t	count(const char *line, const char *mask, char c)
{
	size_t	i;
	size_t 	cnt;

	i = 0;
	cnt = 1;
	while (i < ft_strlen(line))
	{
		if (line[i] == c && mask[i] == SPEC_SYMBOL)
			cnt++;
		i++;
	}
	return (cnt);
}

static void		free_split(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

static size_t length_of_part(const char *line, const char *mask, char c,
size_t i)
{
	size_t	len;

	len = 0;
	while (line[i])
	{
		if (line[i] == c && mask[i] == SPEC_SYMBOL)
			break ;
		i++;
		len++;
	}
	return (len);
}

static void assign(const char *line, char *ptr, const char *mask, size_t *i,
				   char c)
{
	size_t	len;
	size_t 	j;
	size_t 	end;

	j = 0;
	len = length_of_part(line, mask, c, *i);
	end = *i + len;
	while (*i < end)
		ptr[j++] = line[(*i)++];
	ptr[j] = '\0';
	if (line[(*i)] == c)
		(*i)++;
}

char 	**split_symbols(const char *line, const char *mask, char c)
{
	char	**ptr;
	size_t	i;
	size_t	j;

	ptr = (char**)malloc(sizeof(char*) * count(line, mask, c) + 1);
	if (!ptr)
		return (0);
	i = 0;
	j = 0;
	while (line[i])
	{
		ptr[j] = (char*)malloc(length_of_part(line, mask, c, i) + 1);
		if (!ptr[j])
		{
			free_split(ptr);
			return (0);
		}
		assign(line, ptr[j], mask, &i, c);
		j++;
	}
	ptr[j] = 0;
	return (ptr);
}

