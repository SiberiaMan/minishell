#include "minishell.h"

static void	mask_handler_normal(char *line, char *mask)
{
	size_t 	i;

	i = 0;
	while (i < ft_strlen(line))
	{
		if (mask[i] == OPEN_QUOTE)
		{
			while (mask[++i] != CLOSE_QUOTE);
			i++;
		}
		if (line[i] && line[i] == 92 && line[i + 1]
		&& (ft_strchr("<>|;$'\"",line[i + 1])))
		{

			mask[i] = UNUSED_BACKSLASH;
			mask[i + 1] = FAKE_SPEC_SYMBOL; // "\$..."
			i++;
		}
		else if (line[i] && ((line[i] == 92 && line[i + 1] && line[i + 1] == 92)
		|| (line[i] == 92 && !line[i + 1])))
		{
			mask[i] = UNUSED_BACKSLASH; // "\\"
			i += 2;
		}
		else if (line[i] && line[i] == 92 && line[i + 1]
		&& (!ft_strchr("<>|;$'\"",line[i + 1])))
			mask[i++] = UNUSED_BACKSLASH;
		else if (line[i] && (ft_strchr("<>|;$", line[i])) && mask[i] == '1')
			mask[i++] = SPEC_SYMBOL;
		else
			i++;
	}
}

static void mask_handler_real(char *line, char *mask)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (mask[i] == OPEN_QUOTE)
		{
			while (mask[++i] != CLOSE_QUOTE);
			i++;
		}
		if (ft_strchr("<>|;$", line[i])) // экранирование либо 5 либо 1
			mask[i] = SPEC_SYMBOL;
		i++;
	}
}

char 		*get_mask_real(char *line) // get real form
{
	size_t	len;
	size_t	i;
	char 	*mask;

	i = 0;
	len = ft_strlen(line);
	if (!(mask = ft_calloc(ft_strlen(line) + 1, sizeof(char))))
		return (0);
	while (i < len)
		mask[i++] = '1';
	mask_handler_real(line, mask);
	return (mask);
}

char 		*get_mask_normal(char *line)	 // get normal form !!!
{
	size_t 	len;
	size_t 	i;
	char	*mask;

	i = 0;
	len = ft_strlen(line);
	if (!(mask = ft_calloc(ft_strlen(line) + 1, sizeof(char))))
		return (0);
	while (i < len)
		mask[i++] = '1';
	if (!quotes_handler(line, mask))
	{
		write(2, "syntax error with quotes\n",ft_strlen("syntax error with quotes\n"));
		free(mask);
		return (0);
	}
	mask_handler_real(line, mask);
	mask_handler_normal(line, mask);
	return (mask);
}

/*int main() {
	char *str = "'\\'";
	int *mask = get_mask_normal(str);
	for (int i = 0; i < ft_strlen(str); i++)
		printf("%d ", mask[i]);
} */

