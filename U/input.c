#include "history.h"

int comparison(t_gnl *gnl)
{
	if(!ft_strcmp(gnl->str, "\e[D"))
		ft_memset(gnl->str, 0, 10);
	if(!ft_strcmp(gnl->str, "\e[C"))
		ft_memset(gnl->str, 0, 10);
	if(!ft_strcmp(gnl->str, "\t"))
		ft_memset(gnl->str, 0, 10);
	if(!ft_strcmp(gnl->str, "\n"))
		return(enter(gnl));
	if (!ft_strcmp(gnl->str, "\e[A"))
		up(gnl);
	else if (!ft_strcmp(gnl->str, "\e[B"))
		down(gnl);
	else if (ft_strcmp(gnl->str, "\n"))
		get_command(gnl);
	if (!ft_strcmp(gnl->str, "\177"))
		backspace(gnl);
	if(!ft_strcmp(gnl->str, "\4"))
	{
		if (ft_strlen(gnl->edit) == 1)
			ctrl_d(gnl);
	}
	return(0);
}

int input(t_gnl *gnl)
{
	tputs("minishell=):", 1, ft_putint);
	tputs(save_cursor, 1, ft_putint);
	while (1)
	{
		set_terminal(gnl->term_name, gnl->term, gnl->reset_term, 1);
		ft_memset(gnl->str, 0, 10);
		gnl->l = read(0, gnl->str, 10);
		if (comparison(gnl) == 1)
		{
			set_terminal(gnl->term_name, gnl->term, gnl->reset_term, 0);
			//parser(gnl->history->line)
		}
	}
	return(0);
}