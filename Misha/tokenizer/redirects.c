#include "tokenizer.h"

static size_t get_cnt_redirect(t_line_n_mask l_n_m, size_t start)
{
	size_t	cnt;

	cnt = 0;
	while ((l_n_m.line[start] == ' ' && l_n_m.mask[start] == '1')
		   || (l_n_m.mask[start] == UNUSED_BACKSLASH))
		start++;
	while (condition_redirects3(l_n_m, start))
	{
		if ((l_n_m.line[start] == '\\' && l_n_m.mask[start] == UNUSED_BACKSLASH)
			|| (l_n_m.mask[start] == OPEN_QUOTE)
			|| (l_n_m.mask[start] == CLOSE_QUOTE))
			start++;
		else if (l_n_m.mask[start] == '1' || l_n_m.mask[start] == SPACE_VISIBLE)
		{
			cnt++;
			start++;
		}
		else if (l_n_m.line[start] == '$' && l_n_m.mask[start] == SPEC_SYMBOL)
			cnt += get_cnt_dollar(l_n_m, &start); // &(++start)
	}
	return (cnt);
}

static void	change_mask(t_line_n_mask l_n_m, size_t j, size_t start)
{
	while (j < start)
		l_n_m.mask[j++] = UNUSED_SYMBOL;
}

char	*get_redir(t_line_n_mask l_n_m, size_t start, char **line) // not 25
{
	size_t	cnt;
	size_t 	i;
	size_t	j;

	i = 0;
	j = start;
	if (*line)
		free(*line);
	cnt = get_cnt_redirect(l_n_m, start); // big function
	*line = (char*)malloc(sizeof(char) * cnt + 1);
	////if (!line)
	//// exit
	while ((l_n_m.line[start] == ' ' && l_n_m.mask[start] == '1')
		   || (l_n_m.mask[start] == UNUSED_BACKSLASH))
		start++;
	while (condition_redirects3(l_n_m, start))
		if ((l_n_m.line[start] == '\\' && l_n_m.mask[start] == UNUSED_BACKSLASH)
			|| (l_n_m.mask[start] == OPEN_QUOTE) || (l_n_m.mask[start] ==
			CLOSE_QUOTE))
			start++;
		else if (l_n_m.mask[start] == '1' || l_n_m.mask[start] == SPACE_VISIBLE)
			(*line)[i++] = l_n_m.line[start++];
		else if (l_n_m.line[start] == '$' && l_n_m.mask[start] == SPEC_SYMBOL)
			handle_string_dollar(l_n_m, *line, &start, &i);
	change_mask(l_n_m, j, start);
	(*line)[i] = '\0';
	printf("%s\n", *line);
	return (*line);
}

size_t handle_redirects(t_line_n_mask l_n_m, t_token *token, size_t i)
{
	while (l_n_m.line[i] && !(l_n_m.line[i] == '|'
	&& l_n_m.mask[i] == SPEC_SYMBOL) && (l_n_m.mask[i] != CURRENT_SPLIT))
	{
		if (condition_redirects_1(l_n_m, i, '<'))
			token->fd_from = open(get_redir(l_n_m, i + 1, &(token->line)),
			O_RDONLY);
		else if (condition_redirects_2(l_n_m, i, '<'))
		{
			token->fd_from = open(get_redir(l_n_m, i + 2, &(token->line)),
			 O_RDONLY);
			i++;
		}
		else if (condition_redirects_1(l_n_m, i, '>'))
			token->fd_to = open(get_redir(l_n_m, i + 1, &(token->line)), O_RDWR
			| O_CREAT | O_TRUNC, S_IRUSR  | S_IWUSR | S_IRGRP | S_IROTH);
		else if (condition_redirects_2(l_n_m, i, '>'))
		{
			token->fd_to = open(get_redir(l_n_m, i + 2, &(token->line)),
			O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP |
			S_IROTH);
			i++;
		}
		if (!redirect_error(token, &l_n_m))
			return (0);
		i++;
	}
	return (1);
}