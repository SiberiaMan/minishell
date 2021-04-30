#include "history1.h"

char	*realloc_backspace(char *line, t_gnl *gnl)
{
	size_t	i;
	char	*new;
	char	*ptr;

	ptr = line;
	i = ft_strlen(line);
	if (i > 1)
	{
		if (!(new = ft_calloc(i-1, 1)))
			return (NULL);
		new = ft_memcpy(new, line, i-2);
		free(ptr);
	}
	else
	{
		free(gnl->edit);
		new = ft_calloc(1, 1);
		if (!new)
			return (NULL);
	}
	return (new);
}

int	backspace(t_gnl *gnl)
{
	tputs(tgetstr("rc", 0), 1, ft_putint); //restore cursor
	tputs(tgetstr("ce", 0), 1, ft_putint); //чистит до конца строки
	if ((gnl->edit = realloc_backspace(gnl->edit, gnl)))
		ft_putstr(gnl->edit);
return (0);
}

int	up(t_gnl *gnl)
{
	if (gnl->flag == 2)
		gnl->history = gnl->history->prev;
	if (gnl->history)
	{
		char *ptr;

		gnl->flag = 1;
		tputs(tgetstr("rc", 0), 1, ft_putint); //restore cursor
		tputs(tgetstr("ce", 0), 1, ft_putint); //чистит до конца строки
		ptr = gnl->edit;
		gnl->edit = ft_strdup(gnl->history->line);
		free(ptr);
		ft_putstr(gnl->edit);
		if (gnl->history->prev)
			gnl->history = gnl->history->prev;
		else
			gnl->flag = 0;
	}
	return (0);
}

int	down(t_gnl *gnl)
{
	if (gnl->flag == 1)
		gnl->history = gnl->history->next;
	if (gnl->history)
	{
		if (gnl->history->next)
		{
			char *ptr;

			gnl->flag = 2;
			tputs(tgetstr("rc", 0), 1, ft_putint); //restore cursor
			tputs(tgetstr("ce", 0), 1, ft_putint); //чистит до конца строки
			gnl->history = gnl->history->next;
			ptr = gnl->edit;
			gnl->edit = ft_strdup(gnl->history->line);
			free(ptr);
			ft_putstr(gnl->edit);
		}
		else
		{
			tputs(tgetstr("rc", 0), 1, ft_putint); //restore cursor
			tputs(tgetstr("ce", 0), 1, ft_putint); //чистит до конца строки
			gnl->flag = 0;
		}
	}
	return (0);
}
