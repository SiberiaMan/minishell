#include "builtins.h"

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

int	check_entry(char *v, char *e)
{
	int	k;

	k = 0;
	while (e[k] == v[k] && e[k] != '=' && v[k] != '\0')
		k++;
	if (e[k] == '=' && v[k] == '\0')
		return (1);
	return (0);
}

char	**unset(char **vars, char **envp)
{
	char	**ptr1;
	char	**ptr2;
	int		flag;

	ptr1 = vars;
	ptr2 = envp;
	flag = 0;
	while (*ptr2)
	{
		while (*ptr1 && flag == 0)
		{
			if (check_entry(*ptr1, *ptr2) == 0)
				ptr1++;
			else
			{
				flag = 1;
				free(*ptr2);
				*ptr2 = NULL;
			}
		}
		ptr1 = vars;
		ptr2++;
	}
	return (unset_2(envp, count_vars(envp), count_vars(envp) + count_vars
			(vars)));
}
