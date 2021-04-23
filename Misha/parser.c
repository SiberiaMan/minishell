#include "minishell.h"
#include "history.h"

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
		if (line[i] == 34) // double quotes
			cnt_single_quotes++;
		else if (line[i++] == 39) // single quotes
			cnt_double_quotes++;
	if (cnt_double_quotes % 2 || cnt_single_quotes % 2)
		return (0);
	return (1);
}

static size_t 	redirects_syntax(char *line)
{
	size_t	i;

	i = 0;
	while(i < ft_strlen(line))
	{
		if ((!i && line[i] == '<' && line[i + 1] && line[i + 1] == '<'
		&& !line[i + 2]) || !i && line[i] == '<' && !line[i + 1])
			return (0); // 0<<0 // 0<0
		if ((!i && line[i] == '>' && line[i + 1] && line[i + 1] == '>'
			&& !line[i + 2]) || (!i && line[i] == '>' && !line[i + 1]))
			return (0); // 0>>0 // 0>0
		if ((line[i] == '<' && line[i + 1] && line[i + 1] =='>')
		|| line[i] == '>' && line[i + 1] && line[i + 1] == '<')
			return (0);
		if (i == ft_strlen(line) - 1 && (line[i] == '<' || line[i] == '>'))
			return (0);
		if ((line[i] == '<' && line[i + 1] && line[i + 1] == '<' && line[i + 2]
		&& line[i + 2] == '<' ) || (line[i] == '>' && line[i + 1]
		&& line[i + 1] == '>' && line[i + 2] && line[i + 2] == '>'))
			return (0);
		i++;
	}
	return (1);
}

static size_t	pipe_syntax(char *line)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(line);
	i = 0;
	while (i < len)
	{
		if ((i == len - 1 || i == 0) && line[i] == '|')
			return (0);
		if (line[i] == '|' && (line[i + 1] == '|' || line[i - 1] == '|'
		|| line[i - 1] == ';' || line[i + 1] == ';' || line[i - 1] == '<'
		|| line[i - 1] == '>' && line[i + 1] == '>' || line[i + 1] == '<'))
			return (0);
		i++;
	}
	return (1);
}

static size_t	semicolon_syntax(char *line)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(line);
	i = 0;
	while (i < len)
	{
		if ((i == len - 1 || i == 0) && line[i] == ';')
			return (0);
		if (line[i] == ';' && (line[i + 1] == ';' || line[i - 1] == ';'
		|| line[i - 1] == '|' || line[i + 1] == '|' || line[i - 1] == '<'
		|| line[i - 1] == '>' && line[i + 1] == '>' || line[i + 1] == '<'))
			return (0);
		i++;
	}
	return (1);
}

int	parser(char *line) // get normal form
{
	if (!cnt_quotes(line))
	{
		write(2, "syntax error with quotes\n",ft_strlen("syntax error with quotes\n"));
		return(0); // Error code of syntax checking in bash
	}
	if (!redirects_syntax(line))
	{
		print_syntax_err("'newline'\n");
		return (0);
	}
	if (!pipe_syntax(line))
	{
		print_syntax_err("|\n");
		return (0);
	}
	if (!semicolon_syntax(line))
	{
		print_syntax_err(";\n");
		return (0);
	}
	return (1);
}