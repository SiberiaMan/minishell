#include "termcap.h"

void ft_putstr(char *str)
{
	size_t len;

	len = ft_strlen(str);
	write(1, str, len);
}

int	lst_create_add(t_list **lst, char *line)
{
	t_list	*ptr;
	t_list *new;

	if(!(new = malloc(sizeof(t_list))))
		return(-1);
	new->line = line;
	new->next = NULL;
	new->prev = NULL;
	ptr = *lst;
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
		*lst = new;
	}
	else
		*lst = new;
	return (0);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
		i++;
	}
	return (0);
}