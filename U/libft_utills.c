#include "history.h"

size_t		ft_strlen(const char *s)
{
	int i;

	i = 0;
	if(!s)
		return(0);
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
		ft_bzero(str, count * size);
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
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

char	*ft_strchr(const char *s, int c)
{
	size_t i;

	i = 0;
	while (i < (ft_strlen(s) + 1))
	{
		if (s[i] == c)
			return ((char*)(s + i));
		i++;
	}
	return (NULL);
}

int		ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int		ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int		ft_isalnum(int c)
{
	if (ft_isalpha(c) > 0 || ft_isdigit(c) > 0)
		return (1);
	else
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

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	sim;

	i = 0;
	str = (unsigned char*)b;
	sim = (unsigned char)c;
	while (i < len)
	{
		str[i] = sim;
		i++;
	}
	return (str);
}

