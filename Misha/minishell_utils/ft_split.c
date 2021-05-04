#include "minishell_utils.h"

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

char				**ft_split(char *s, char c)
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
			i += ft_len(s, c, i);
			j++;
		}
		else
			i++;
	ptr[j] = 0;
	free(s);
	return (ptr);
}