#include "minishell_utils.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strchr(s, c) != 0)
	{
		while (i <= ft_strlen(s))
		{
			if (s[i] == c)
				j = i;
			i++;
		}
		return (&((char *)s)[j]);
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

int		ft_isalnum(int c)
{
	if (ft_isalpha(c) > 0 || ft_isdigit(c) > 0)
		return (1);
	else
		return (0);
}
