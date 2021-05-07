#include "termcap.h"
#include "../builtins/builtins.h"

void	ft_lstclear(t_list *history, int flag)
{
	t_list *start;
	t_list *ptr;

	if(flag != 0)
	{
		while (history->next)
			history = history->next;
	}
	start = history;
	while(start)
	{
		ptr = start->prev;
		free(start->line);
		free(start);
		start = ptr;
	}
	history = NULL;
}

void free_gnl_error(t_gnl *gnl)
{
	if(gnl->str)
		free(gnl->str);
	if(gnl->edit)
		free(gnl->edit);
	if(gnl->term)
		free(gnl->term);
	if(gnl->history)
		ft_lstclear(gnl->history, gnl->flag);
	if (gnl->env)
		free_vars(*(gnl->env), count_vars(*(gnl->env)) - 1);
	set_terminal(gnl->term_name, gnl->term, gnl->reset_term, 0);
	exit(0);
}

void free_gnl(t_gnl *gnl)
{
	if(gnl->str)
		free(gnl->str);
	if(gnl->edit)
		free(gnl->edit);
	if(gnl->term)
		free(gnl->term);
	if(gnl->history)
		ft_lstclear(gnl->history, gnl->flag);
	if (gnl->env)
		free_vars(*(gnl->env), count_vars(*(gnl->env)) - 1);
	set_terminal(gnl->term_name, gnl->term, gnl->reset_term, 0);
}

t_gnl *gnl_init(void)
{
	t_gnl *tmp;

	tmp = malloc(sizeof(t_gnl));
	if(!tmp)
		return(NULL);
	tmp->flag = 0;
	tmp->term_name = (char*)(getenv("TERM"));
	tmp->term = malloc(sizeof(struct termios));
	if(!tmp->term)
		return(NULL);
	tmp->reset_term = malloc(sizeof(struct termios));
	if(!tmp->reset_term)
		return(NULL);
	tmp->history = NULL;
	tmp->edit = ft_calloc(1,1);
	if(!tmp->edit)
		return(NULL);
	tmp->str = ft_calloc(10, 1);
	if(!tmp->str)
		return(NULL);
	tmp->env = 0;
	return(tmp);
}

//int check_for_exit(char *line, t_gnl *gnl)
//{
//	char *ptr;
//	size_t i;
//
//	(void)(gnl);
//	i = 0;
//	ptr = line;
//	while(*ptr == ' ')
//	{
//		i++;
//		ptr++;
//	}
//	if(!ft_strcmp(ptr, "exit"))
//	{
//		write(1, "\n", 1);
//		write(1, "exit\n", 6);
//		free_gnl(gnl);
//	}
//	return(0);
//}

int ctrl_d(t_gnl *gnl)
{
	write(1, " exit\n", 6);
	free_gnl(gnl);
	return(0);
}