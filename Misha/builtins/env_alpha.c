#include "builtins.h"

void	print_envp(char **envp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		while(envp[i][j] != '=' && envp[i][j] != '\0')
		{
			ft_putchar_fd(envp[i][j], 1);
			j++;
		}
		if(envp[i][j] == '=' && envp[i][j + 1] != '\0')
		{
			ft_putstr_fd("=\"", 1);
			j++;
			while (envp[i][j] != '\0')
			{
				ft_putchar_fd(envp[i][j], 1);
				j++;
			}
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		j = 0;
		i++;
	}
}

void	sort_vars(char **v)
{
	int i;
	int j;
	int flag;
	char *tmp;
	int count;

	i = 0;
	j = 0;
	flag = 1;
	count = count_vars(v);
	count++;
	while (count > 0)
	{
		i = 0;
		while (v[i] && v[i + 1] && i <= count)
		{
			flag = 1;
			while(v[i][j] == v[i + 1][j] && v[i][j+1] != '=' && v[i][j+1] !=
				'\0' && v[i+1][j+1] != '=' && v[i+1][j+1] != '\0')
			{
				j++;
			}
			if (v[i][j] - v[i + 1][j] > 0)
			{
				tmp = v[i];
				v[i] = v[i + 1];
				v[i + 1] = tmp;
			}
			j = 0;
			i++;
		}
		count--;
	}
	print_envp(v);
}