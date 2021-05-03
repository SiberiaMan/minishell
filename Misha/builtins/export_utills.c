#include "builtins.h"

void	free_vars(char **vars, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free(vars[j]);
		j++;
	}
	free(vars);
	vars = NULL;
}

int	count_vars(char **vars)
{
	char	**ptr;
	int		i;

	ptr = vars;
	i = 0;
	while (*ptr)
	{
		i++;
		ptr++;
	}
	return (i);
}

char	**copy_envp(char **envp)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc((sizeof(char *) * (count_vars(envp) + 1)));
	if (!res)
		return (NULL);
	while (envp[i])
	{
		res[i] = ft_strdup(envp[i]);
		if (!res[i])
			free_vars(res, i);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void ft_putstr(char *str)
{
	size_t len;

	len = ft_strlen(str);
	write(1, str, len);
}
