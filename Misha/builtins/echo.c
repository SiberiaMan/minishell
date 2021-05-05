#include "builtins.h"

int	echo_dollar(char *dollar, char **envp)
{
	char	**ptr;
	int		i;

	if (!dollar)
		return (-1);
	i = 0;
	ptr = envp;
	while (ptr[i])
	{
		if (!ft_strncmp(dollar + 1, ptr[i], ft_strlen(dollar + 1)))
			return (i);
		i++;
	}
	return (-1);
}

void	echo_output(char **str, int opt, char **envp, char *spaces)
{
	char	*dollar;
	int		i;
	int		last;
	int		j;

	last = count_vars(str) - 1;
	i = opt + 1;
	while (str[i])
	{
		if (spaces[i] == 'b')
		{
			dollar = ft_strchr(str[i], '$');
			if (dollar)
			{
				j = echo_dollar(dollar, envp);
				if (j >= 0)
					ft_putstr_fd(envp[j] + ft_strlen(dollar), 1);
			}
			else
				ft_putstr_fd(str[i], 1);
			if (i != last)
				ft_putchar_fd(' ', 1);
		}
		i++;
	}
}

int	count_spaces(char **str, int opt, char **envp, char *spaces)
{
	int	ok;
	int	i;
	int	j;

	i = opt + 1;
	ok = 0;
	while (str[i])
	{
		j = echo_dollar(ft_strchr(str[i], '$'), envp);
		if (j >= 0)
		{
			spaces[i] = 'b';
			ok = 1;
		}
		else if (!ft_strcmp(str[i], "-n") && ok == 1 )
			spaces[i] = 'b';
		else if (ft_strcmp(str[i], "-n") && !ft_strchr(str[i], '$'))
		{
			ok = 1;
			spaces[i] = 'b';
		}
		i++;
	}
	echo_output(str, opt, envp, spaces);
	return (0);
}

int	ft_echo(char **str, char **envp)
{
	int		i;
	int		opt;
	char	spaces[100];

	ft_memset(spaces, 'a', 100);
	i = 1;
	opt = 0;
	if (str[1] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	else if (!ft_strcmp(str[1], "-n"))
	{
		opt = 1;
		i++;
	}
	if (opt == 1 && str[2] == NULL)
		return (0);
	count_spaces(str, opt, envp, spaces);
	if (opt == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}