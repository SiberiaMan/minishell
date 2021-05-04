#include "minishell_utils.h"

static int	ft_tolower(int c)
{
	if (('A' <= c) && (c <= 'Z'))
		return (c + 32);
	return (c);
}

void	to_lower(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		line[i] = ft_tolower(line[i]);
		i++;
	}
}
