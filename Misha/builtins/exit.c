#include "builtins.h"

void	free_and_exit_tokenizer_2(t_line_n_mask *l_n_m)
{
	size_t	j;

	j = 0;
	free_gnl(l_n_m->gnl);
	free (l_n_m->mask);
	if (l_n_m->pids)
		free(l_n_m->pids);
	if (l_n_m->pipes)
	{
		while (j < l_n_m->cnt_pipes + 1)
			free(l_n_m->pipes[j++]);
		free(l_n_m->pipes);
	}
	if (l_n_m->free_line)
		free(*l_n_m->free_line);
}

void	free_token_n_structure_exit_2(t_token *token, t_line_n_mask *l_n_m)
{
	size_t	j;

	j = 0;
	while (token->args[j])
		free(token->args[j++]);
	free(token->args);
	free(token->lower);
	free_and_exit_tokenizer_2(l_n_m);
}

long long		ft_atoi(const char *str)
{
	long long		a;
	int				i;
	int				mn;

	i = 0;
	a = 0;
	mn = 1;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r') && str[i] != '\0')
		i++;
	if (str[i] == '-')
		mn = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		a = a * 10 + (str[i] - 48) * mn;
		i++;
	}
	return (a);
}

void exit_error(int error, char *arg)
{
	if (error == 1)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	if (error == 2)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
}

int all_digits(char *line)
{
	char *ptr;

	ptr = line;
	while(ft_isdigit(*ptr) && *ptr != '\0')
		ptr++;
	if (*ptr == '\0')
		return(1);
	return(-1);
}

int ft_exit(t_line_n_mask *l_n_m, t_token *token)
{
	long long a;

	if (!(token->args[1]))
		a = 0;
	else if (token->args[2])
	{
		exit_error(1, NULL);
		return (1);
	}
	else
	{
		if (all_digits(token->args[1]) == -1)
		{
			a = 255;
			exit_error(2, token->args[1]);
		}
		else
		{
			a = ft_atoi(token->args[1]);
			if ((token->args[1][0] == '-' && a > 0) ||
				(token->args[1][0] != '-' && a < 0))
			{
				exit_error(2, token->args[1]);
				a = 255;
			}
		}
	}
	free_token_n_structure_exit_2(token, l_n_m);
	ft_putstr_fd("exit\n", 1);
	exit (a);
}