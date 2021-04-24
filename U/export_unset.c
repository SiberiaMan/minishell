#include <stdlib.h>
#include <stdio.h>
#include "history.h"

void	free_vars(char **vars)
{
	while (*vars)
	{
		free(*vars);
		vars++;
	}
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

char	**export(char **vars, char **envp)
{
	char	**res;
	int		i;
	int		j;

	j = 0;
	i = count_vars(vars) + count_vars(envp);
	res = (char **)malloc((sizeof(char *) * (i + 1)));
	if (!res)
		return (0);
	while (*vars)
	{
		res[j] = ft_strdup(*vars);
		vars++;
		j++;
	}
	while (*envp)
	{
		res[j] = ft_strdup(*envp);
		envp++;
		j++;
	}
	res[j] = NULL;
	free_vars(envp);
	free_vars(vars);
	return (res);
}

char	**unset_2(char **envp, int j, int len)
{
	int		k;
	int		i;
	char	**ptr;
	char	**res;

	k = 0;
	i = 0;
	res = (char **)malloc((sizeof(char *) * (len)));
	if (!res)
		return (NULL);
	ptr = envp;
	while (k < j)
	{
		if (*ptr != NULL)
		{
			res[i] = ft_strdup(*ptr);
			i++;
		}
		ptr++;
		k++;
	}
	res[len] = NULL;
	return (res);
}

char	**unset(char **vars, char **envp)
{
	char	**ptr1;
	char	**ptr2;
	int		i;
	int		j;

	ptr1 = vars;
	ptr2 = envp;
	i = count_vars(vars);
	j = count_vars(envp);
	while (*ptr2)
	{
		while (*ptr1)
		{
			if (!strcmp(*ptr2, *ptr1))
			{
				free(*ptr2);
				*ptr2 = NULL;
				break ;
			}
			ptr1++;
		}
		ptr1 = vars;
		ptr2++;
	}
	return (unset_2(envp, j, i + j));
}

int	main(int argc, char **argv, char **envp)
{
	char	**res;
	char	**res2;
	char	**ptr;

	res = export(argv, envp);
	ptr = res;
	while (*ptr)
	{
		printf("%s\n", *ptr);
		ptr++;
	}
	printf("\n\n\n");
	res2 = unset(argv, res);
	while (*res2)
	{
		printf("%s\n", *res2);
		res2++;
	}
	return (0);
}
