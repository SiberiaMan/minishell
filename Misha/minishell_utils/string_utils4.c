#include "minishell_utils.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t i;
	size_t j;

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