#include "history.h"

size_t		ft_strlen(const char *s)
{
	int i;

	i = 0;
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

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	char	*bptr;

	ptr = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (0);
	bptr = ptr;
	while (*s1)
	{
		*ptr = *s1;
		ptr++;
		s1++;
	}
	while (*s2)
	{
		*ptr = *s2;
		ptr++;
		s2++;
	}
	*ptr = '\0';
	return (bptr);
}

char		*ft_strjoin_space(char const *s1, char const *s2)
{
	char	*ptr;
	char	*bptr;

	ptr = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!ptr)
		return (0);
	bptr = ptr;
	while (*s1)
	{
		*ptr = *s1;
		ptr++;
		s1++;
	}
	*ptr = ' ';
	ptr++;
	while (*s2)
	{
		*ptr = *s2;
		ptr++;
		s2++;
	}
	*ptr = '\0';
	return (bptr);
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

static	size_t		ft_count(char const *s, char c)
{
	size_t		i;
	size_t		cnt;

	i = 0;
	cnt = 0;
	if (s[i] != c)
	{
		cnt++;
		i++;
	}
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c)
			cnt++;
		i++;
	}
	return (cnt);
}

static	void		ft_free(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr[i]);
}

static	void		ft_assign(char const *s, size_t from, size_t to, char *ptr)
{
	while (from < to)
	{
		*ptr = s[from];
		from++;
		ptr++;
	}
	*ptr = '\0';
}

static	size_t		ft_len(char const *s, char c, size_t start)
{
	size_t	size;

	size = 0;
	while (s[start] && s[start] != c)
	{
		size++;
		start++;
	}
	return (size);
}

char				**ft_split(char const *s, char c)
{
	char		**ptr;
	size_t		i;
	size_t		j;

	ptr = (char**)malloc(sizeof(char*) * (ft_count(s, c) + 1));
	if (!ptr)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
		if (s[i] != c)
		{
			if (!(ptr[j] = (char*)malloc(ft_len(s, c, i) + 1)))
			{
				ft_free(ptr);
				return (0);
			}
			ft_assign(s, i, i + ft_len(s, c, i), ptr[j]);
			//printf("%s\n", ptr[j]);
			i += ft_len(s, c, i);
			j++;
		}
		else
			i++;
	ptr[j] = 0;
	return (ptr);
}