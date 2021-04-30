#include "history.h"

int	enter(t_gnl *gnl)
{
	check_for_exit(gnl->edit, gnl);
	write(1, "\n", 1);
	tputs("minishell=):", 1, ft_putint);
	tputs(save_cursor, 1, ft_putint);
	if (gnl->edit[0] != '\0')
	{
		lst_create_add(&gnl->history, ft_strdup(gnl->edit));
		free(gnl->edit);
		gnl->edit = ft_calloc(1, 1);
		if (!gnl->edit)
			free_gnl(gnl);
		gnl->flag = 0;
		return (1);
	}
	else
	{
		if (gnl->history)
			while (gnl->history->next)
				gnl->history = gnl->history->next;
	}
	return (0);
}

int	get_command(t_gnl *gnl)
{
	char	*ptr;

	ptr = gnl->edit;
	write(1, gnl->str, gnl->l);
	gnl->edit = ft_strjoin(gnl->edit, gnl->str);
	free(ptr);
	return (0);
}
