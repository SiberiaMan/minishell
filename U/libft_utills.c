#include "history.h"

size_t		ft_strlen(const char *s)
{
	int i;

	i = 0;
	// if(!s)
	// 	return(0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char *str;

	str = (unsigned char*)s;
	while (n-- > 0)
		str[n] = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	char *str;

	if (!(str = (void *)malloc(count * size)))
		return (0);
	else
	{
		ft_bzero(str, count * size);
		return (str);
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
	{
		return (0);
	}
	if (!(str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char))))
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char*)src;
	str2 = (unsigned char*)dst;
	if (!src && !dst)
		return (dst);
	while (i < n)
	{
		str2[i] = str1[i];
		i++;
	}
	return (str2);
}

char	*ft_strdup(const char *s1)
{
	int i;
	char*s2;

	i = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	if (!(s2 = (char*)malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int ft_putint(int c)
{
    return(write(STDOUT_FILENO, &c, 1));
}

void ft_putstr(char *str)
{
    while(*str)
    {
        write(1, str, 1);
        str++;
    }
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

void lst_add(t_list **lst, t_list *new)
{
	t_list	*ptr;

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

}

void list_swap(t_list *a, t_list *b)
{
	t_list *c;

	c = a;
	a = b;
	b = c;
}