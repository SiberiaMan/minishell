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

void	exit_error(int error, char *arg)
{
	if (error == 1)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	if (error == 2)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
}

int	ft_norm_exit(t_line_n_mask *l_n_m, t_token *token)
{
	long long	a;

	if (!(token->args[1]))
	{
		a = 0;
		ft_putstr_fd("exit\n", 1);
	}
	else if (token->args[1] && !token->args[2])
	{
		if (all_digits(token->args[1]) == -1)
		{
			a = 255;
			exit_error(2, token->args[1]);
		}
		else
		{
			a = ft_atoi(token->args[1]);
			if ((token->args[1][0] == '-' && a > 0) || (token->args[1][0] !=
				'-' && a < 0))
			{
				exit_error(2, token->args[1]);
				a = 255;
			}
			else
				ft_putstr_fd("exit\n", 1);
		}
	}
	free_token_n_structure_exit_2(token, l_n_m);
	exit (a);
}

int	ft_exit(t_line_n_mask *l_n_m, t_token *token)
{
	int count;

	count = count_vars(token->args);
	if (count < 3)
		ft_norm_exit(l_n_m, token);
	exit_error(1, NULL);
	return (1);
}
