#include "builtins.h"

void exit_error(int error)
{
	if (error == 1)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
}

int ft_exit(t_line_n_mask *l_n_m, t_token *token)
{
	int a;

	if (!(token->args[1]))
	{
		free_token_n_structure_exit(token, l_n_m);
		///gnl там чистится?
		return (0);
	}
	if (token->args[2])
	{
		exit_error(1);
		return(1);
	}
	else
	{
		///unsigned char 256
		exit(123456789);
	}
}