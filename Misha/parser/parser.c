#include "parser.h"

static size_t	redirect_syntax_2(const char *line, const char *mask, size_t i)
{
	if (i == ft_strlen(line) - 1 && ((line[i] == '<' && mask[i] == SPEC_SYMBOL)
			|| (line[i] == '>' && mask[i] == SPEC_SYMBOL)))
		return (0);
	if ((line[i] == '<' && mask[i] == SPEC_SYMBOL && line[i + 1]
			&& line[i + 1] == '<' && mask[i + 1] == SPEC_SYMBOL
			&& line[i + 2] && line[i + 2] == '<' && mask[i + 2] == SPEC_SYMBOL)
		|| (line[i] == '>' && mask[i] == SPEC_SYMBOL && line[i + 1]
			&& line[i + 1] == '>' && mask[i + 1] == SPEC_SYMBOL
			&& line[i + 2] && line[i + 2] == '>' && mask[i + 2] == SPEC_SYMBOL))
		return (0);
	return (1);
}

static size_t	redirect_syntax_1(const char *line, const char *mask, size_t i)
{
	if ((!i && line[i] == '<' && mask[i] == SPEC_SYMBOL
			&& line[i + 1] && line[i + 1] == '<' && mask[i + 1] == SPEC_SYMBOL
			&& !line[i + 2]) || (!i && line[i] == '<' && mask[i] == SPEC_SYMBOL
			&& !line[i + 1]))
		return (0);
	if ((!i && line[i] == '>' && mask[i] == SPEC_SYMBOL
			&& line[i + 1] && line[i + 1] == '>' && mask[i + 1] == SPEC_SYMBOL
			&& !line[i + 2]) || (!i && line[i] == '>' && mask[i] == SPEC_SYMBOL
			&& !line[i + 1]))
		return (0);
	if ((line[i] == '<' && mask[i] == SPEC_SYMBOL
			&& line[i + 1] && line[i + 1] =='>' && mask[i + 1] == SPEC_SYMBOL)
		|| (line[i] == '>' && mask[i] == SPEC_SYMBOL
			&& line[i + 1] && line[i + 1] == '<' && mask[i + 1] == SPEC_SYMBOL))
		return (0);
	return (1);
}

static size_t	redirect_syntax(const char *line, const char *mask)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(line))
	{
		if (!redirect_syntax_1(line, mask, i)
			|| !redirect_syntax_2(line, mask, i))
			return (0);
		i++;
	}
	return (1);
}

static void	move_spaces(const char *line, const char *mask,
int *j, int *k)
{
	while (line[*j] && line[*j] == ' ' && mask[*j] == '1')
		(*j)++;
	while (*k >= 0 && line[*k] == ' ' && mask[*k] == '1')
		(*k)--;
}

static size_t	pipe_syntax(const char *line, const char *mask)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < ft_strlen(line))
	{
		if ((i == ft_strlen(line) - 1 || i == 0) && line[i] == '|'
			&& mask[i] == SPEC_SYMBOL)
			return (0);
		if (line[i] == '|' && mask[i] == SPEC_SYMBOL)
		{
			k = i - 1;
			j = i + 1;
			move_spaces(line, mask, &j, &k);
			if ((mask[j] == SPEC_SYMBOL && line[j] != '$')
				|| (mask[k] == SPEC_SYMBOL && line[j] != '$'))
				return (0);
		}
		i++;
	}
	return (1);
}

static size_t	semicolon_syntax(const char *line, const char *mask)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < ft_strlen(line))
	{
		if (i == 0 && line[i] == ';' && mask[i] == SPEC_SYMBOL)
			return (0);
		if (line[i] == ';' && mask[i] == SPEC_SYMBOL)
		{
			k = i - 1;
			j = i + 1;
			move_spaces(line, mask, &j, &k);
			if ((mask[j] == SPEC_SYMBOL && line[j] != '$')
				|| (mask[k] == SPEC_SYMBOL && line[j] != '$'))
				return (0);
		}
		i++;
	}
	return (1);
}

int	parser(const char *line, const char *mask) // get normal form
{
	if (!redirect_syntax(line, mask))
	{
		print_syntax_err("'<'\n");
		return (0);
	}
	if (!pipe_syntax(line, mask))
	{
		print_syntax_err("|\n");
		return (0);
	}
	if (!semicolon_syntax(line, mask))
	{
		print_syntax_err(";\n");
		return (0);
	}
	return (1);
}
