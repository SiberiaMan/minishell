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

long long	ft_atoi(const char *str)
{
	long long	a;
	int			i;
	int			mn;

	i = 0;
	a = 0;
	mn = 1;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r') && str[i] != '\0')
		i++;
	if (str[i] == '-')
		mn = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		a = a * 10 + (str[i] - 48) * mn;
		i++;
	}
	return (a);
}

int	all_digits(char *line)
{
	char	*ptr;

	ptr = line;
	while (ft_isdigit(*ptr) && *ptr != '\0')
		ptr++;
	if (*ptr == '\0')
		return (1);
	return (-1);
}