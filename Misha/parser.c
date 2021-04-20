#include "minishell.h"
static size_t	cnt_quotes(char *line)
{
	size_t	len;
	size_t 	i;
	size_t 	cnt_single_quotes;
	size_t 	cnt_double_quotes;

	len = ft_strlen(line);
	cnt_single_quotes = 0;
	cnt_double_quotes = 0;
	i = 0;
	while (i < len)
		if (line[i] == 44) // single_quotes
			cnt_single_quotes++;
		else if (line[i++] == 34) // double quotes
			cnt_double_quotes++;
	if (cnt_double_quotes % 2 || cnt_single_quotes % 2)
		return (0);
	return (1);
}

static size_t 	redirects_syntax(char *line)
{

}
int	parser(char *line)
{

}
