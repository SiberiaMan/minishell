#include "minishell.h"

static size_t	get_cnt_after_equal(char *line)
{
	size_t	cnt;
	size_t	i;

	i = 0;
	cnt = 0;
	while (line[i++] != '=')
		;
	while (line[i++])
		cnt++;
	return (cnt);
}

static size_t get_cnt_env(t_line_n_mask l_n_m, size_t *start, size_t j)
{
	size_t	cnt;
	char	*env;
	size_t 	i;

	cnt = j - *start;
	i = 0;
	env = (char*)malloc(sizeof(char) * cnt + 1);
	///if (!env)
		/// exit
	while (*start < j)
		env[i++] = l_n_m.line[*start++];
	env[i] = '\0';
	j = 0;
	while (l_n_m.env[j])
	{
		if (ft_strncmp(env, l_n_m.env[j], ft_strlen(env)))
		{
			free(env);
			return (get_cnt_after_equal(l_n_m.env[j]));
		}
		j++;
	}
	free(env);
	return (0);
}

static size_t get_cnt_dollar(t_line_n_mask l_n_m, size_t *start)
{
	size_t 	j;

	(*start)++;
	j = *start;
	if (!l_n_m.line[*start] || l_n_m.line[*start] == ' ')
	{
		(*start)++;
		return (1); // cnt for dollar
	}
	if ((l_n_m.mask[*start] == UNUSED_BACKSLASH && l_n_m.line[*start + 1]
	&& l_n_m.mask[*start + 1] == SPACE_VISIBLE))
	{
		*start += 2;
		return (2); // cnt for dollar and space
	}
	while (l_n_m.line[j] && !(l_n_m.line[j] == '\"' && l_n_m.mask[j] == '7')
	&& !(l_n_m.line[j] == ' ' && l_n_m.mask[j] == '1')
	&& !(l_n_m.line[j] == '$' && l_n_m.mask[j] == SPEC_SYMBOL)
	&& !(l_n_m.line[j] == '\\' && l_n_m.mask[j] == UNUSED_BACKSLASH))
		j++;
	return (get_cnt_env(l_n_m, start, j)); // cnt for env var
}

static size_t get_cnt_redirect(t_line_n_mask l_n_m, size_t start)
{
	size_t	cnt;

	cnt = 0;
	while ((l_n_m.line[start] == ' ' && l_n_m.mask[start] == '1')
	|| (l_n_m.mask[start] == UNUSED_BACKSLASH))
		start++;
	while (l_n_m.line[start] && ((l_n_m.mask[start] == '1'
	&& !(l_n_m.mask[start] == '1' && l_n_m.line[start] == ' '))
	|| (l_n_m.mask[start] == '$' && l_n_m.mask[start] == UNUSED_BACKSLASH)))
	{
		if (l_n_m.line[start] == '\\' && l_n_m.mask[start] == '5')
			start++;
		else if (l_n_m.mask[start] == '1')
		{
			cnt++;
			start++;
		}
		else if (l_n_m.line[start] == '$' && l_n_m.mask[start] == SPEC_SYMBOL)
			cnt += get_cnt_dollar(l_n_m, &start); // &(++start)
	}
	return (cnt);
}

static char *get_env_rvalue(char *line)
{
	size_t	i;
	size_t 	j;
	char	*env_rvalue;
	size_t	cnt;

	i = 0;
	j = 0;
	cnt = get_cnt_after_equal(line);
	env_rvalue = (char*)malloc(sizeof(char) * cnt + 1);
	///if (!env_rvalue)
		/// exit
	while (line[i++] != '=')
		;
	while (line[i])
		env_rvalue[j++] = line[i++];
	env_rvalue[j] = '\0';
	return (env_rvalue);
}

static char	*get_env_string(t_line_n_mask l_n_m, size_t *start, size_t j)
{
	char 	*env_lvalue;
	size_t 	cnt;
	size_t 	i;

	i = 0;
	cnt = j - *start;
	env_lvalue = (char*)malloc(sizeof(cnt) + 1);
	///if (!env_lvalue)
		/// exit
	while (*start < j)
		env_lvalue[i++] = l_n_m.line[*start++];
	env_lvalue[i] = '\0';
	j = 0;
	while (l_n_m.env[j])
	{
		if (ft_strncmp(l_n_m.env[j], env_lvalue, ft_strlen(env_lvalue)))
		{
			free(env_lvalue);
			return (get_env_rvalue(l_n_m.env[j]));
		}
		j++;
	}
	free(env_lvalue);
	return ("");
}

static void	append_line(char *line, char *env, size_t *i)
{
	size_t j;

	j = 0;
	while (env[j])
		line[(*i)++] = env[j++];
}

static void	handle_string_dollar(t_line_n_mask l_n_m, char *line,
size_t *start, size_t *i)
{
	size_t	j;
	char 	*env;

	(*start)++;
	j = *start;
	if (!l_n_m.line[*start] || l_n_m.line[*start] == ' ')
	{
		line[(*i)++] = '$';
		(*start)++;
		return ;
	}
	if ((l_n_m.mask[*start] == '5' && l_n_m.line[*start + 1]
	&& l_n_m.mask[*start + 1] == SPACE_VISIBLE))
	{
		line[(*i)++] = '$';
		line[(*i)++] = ' ';
		(*start) += 2;
		return ; // cnt for dollar and space
	}
	while (l_n_m.line[j] && !(l_n_m.line[j] == '\"' && l_n_m.mask[j] == '7')
	&& !(l_n_m.line[j] == ' ' && l_n_m.mask[j] == '1') && !(l_n_m.line[j] == '$'
	&& l_n_m.mask[j] == SPEC_SYMBOL) && !(l_n_m.line[j] == '\\'
	&& l_n_m.mask[j] == UNUSED_BACKSLASH))
		j++;
	env = get_env_string(l_n_m, start, j);
	append_line(line, env, i);
}

char	*get_redirect(t_line_n_mask l_n_m, size_t start, char **line) // not 25
{
	size_t	cnt;
	size_t 	i;

	i = 0;
	if (*line)
		free(line);
	cnt = get_cnt_redirect(l_n_m, start); // big function
	*line = (char*)malloc(sizeof(char) * cnt + 1);
	////if (!line)
		//// exit
	while ((l_n_m.line[start] == ' ' && l_n_m.mask[start] == '1')
	|| (l_n_m.mask[start] == UNUSED_BACKSLASH))
		start++;
	while (l_n_m.line[start] && ((l_n_m.mask[start] == '1'
	&& !(l_n_m.mask[start] == '1' && l_n_m.line[start] == ' '))
	|| (l_n_m.mask[start] == '$') || (l_n_m.mask[start] == UNUSED_BACKSLASH)))
	{
		if ((l_n_m.line[start] == '\\' && l_n_m.mask[start] == UNUSED_BACKSLASH)
		|| (l_n_m.mask[start] == OPEN_QUOTE) || (l_n_m.mask[start] ==
		CLOSE_QUOTE))
			start++;
		else if (l_n_m.mask[start] == '1')
			(*line)[i++] = l_n_m.line[start++];
		else if (l_n_m.line[start] == '$' && l_n_m.mask[start] == SPEC_SYMBOL)
			handle_string_dollar(l_n_m, *line, &start, &i);
	}
	(*line)[i] = '\0';
	printf("%s\n", *line);
	return (*line);
}

int	redirect_error(char *line)
{
	char *error;

	error = ": No such file or directory\n";
	write(2, line, ft_strlen(line));
	write(2, error, ft_strlen(error)); ///status?
	return (0);
}

static int 	handle_redirects(t_line_n_mask l_n_m, t_pipes_n_pids p_n_pds,
t_token *token, size_t i)
{
	int		fdin;
	int		fdout;

	while (l_n_m.line[i] && !(l_n_m.line[i] == '|' && l_n_m.mask[i] ==
	SPEC_SYMBOL) && (l_n_m.mask[i] != CURRENT_SPLIT))
	{
		if (l_n_m.line[i] == '<' && l_n_m.mask[i] == SPEC_SYMBOL
		&& l_n_m.line[i + 1] != '<')
			token->fd_from = open(get_redirect(l_n_m, i + 1, &(token->line)),
					O_RDONLY);
		else if (l_n_m.line[i] == '<' && l_n_m.mask[i] == SPEC_SYMBOL
		&& l_n_m.line[i + 1] == '<')
			token->fd_from = open(get_redirect(l_n_m, i + 2, token->line),
					  O_RDONLY);
		else if (l_n_m.line[i] == '>' && l_n_m.mask[i] == SPEC_SYMBOL
		&& l_n_m.line[i + 1] != '>')
			token->fd_to = open(get_redirect(l_n_m, i + 1, 0), O_WRONLY |
			O_TRUNC | O_CREAT);
		else if (l_n_m.line[i] == '>' && l_n_m.mask[i] == SPEC_SYMBOL
		&& l_n_m.line[i + 1] == '>')
			token->fd_to = open(get_redirect(l_n_m, i + 2, 0), O_WRONLY |
			O_APPEND | O_CREAT);
		if (token->fd_from < 0)
			return (redirect_error(token->line));
		i++;
	}
	return (1);
}

t_token tokenizer(t_line_n_mask l_n_m, t_pipes_n_pids p_n_pds, size_t *i,
int j)
{
	t_token temp;

	if (j == 0)
		temp.pipe_from = 0;
	if (j == p_n_pds.cnt_pipes)
		temp.pipe_to = 0;

}

t_token token_init(void)
{
	return ((t_token) {
		.args = 0,
		.line = 0,
		.fd_from = 0,
		.fd_to = 0,
		.pipe_to = 0,
		.pipe_from = 0,
		.is_from = 0,
		.is_to = 0
	});
}

static size_t	kernel(t_line_n_mask l_n_m, t_pipes_n_pids p_n_pds, size_t i,
int *status)
{
	int 	fdin;
	int 	fdout;
	size_t	j;
	t_token	temp_cmd;

	j = 0;
	fdin = dup(0);
	temp_cmd = token_init();
	handle_redirects(l_n_m, p_n_pds, &temp_cmd, 0);
	/*while (j < p_n_pds.cnt_pipes + 1)
	{
		temp_cmd = tokenizer(l_n_m, p_n_pds, &i, j);
		if (j == p_n_pds.cnt_pipes)
		{

		}
	} */
}

static size_t handle_pipes(t_line_n_mask l_n_m, size_t i, int *status)
{
	int				cnt_pipes;
	t_pipes_n_pids	p_n_pds;

	cnt_pipes = 0;
	while (l_n_m.line[i] && l_n_m.mask[i] != CURRENT_SPLIT)
	{
		if (l_n_m.line[i] == '|' && l_n_m.mask[i] == SPEC_SYMBOL)
			cnt_pipes++;
		i++;
	}
	p_n_pds.pipes = (int**)malloc(sizeof(int[2]) * cnt_pipes);
	if (!p_n_pds.pipes) // exit program + status ?
		return (0);
	p_n_pds.pids = (int*)malloc(sizeof(int) * cnt_pipes + 1);
	if (!p_n_pds.pids) // exit program + status ?
	{
		free(p_n_pds.pipes);
		return (0);
	}
	p_n_pds.cnt_pipes = cnt_pipes;
	kernel(l_n_m, p_n_pds, i, status);
	return (0);
}

static void	handle_semicolons(const char *line, char *mask, char **env,
int *status)
{
	size_t			i;
	size_t			j;
	t_line_n_mask	l_n_m;

	i = 0;
	j = 0;
	l_n_m.mask = mask;
	l_n_m.line = line;
	l_n_m.env = env;
	while (line[i])
	{
		if (line[i] == ';' && mask[i] == SPEC_SYMBOL)
		{
			mask[i] = CURRENT_SPLIT;
			handle_pipes(l_n_m, j, status);
			j = i + 1;
		}
		i++;
	}
	handle_pipes(l_n_m, j, status);
}

static size_t	parse_n_execute(char *line, char **env, int *status) // входит
// изначальная "грязная
// "команда
{
	char 	*mask;

	if (!(mask = get_mask_normal(line)))
		return (0);
	printf("%s\n", line);
	printf("%s\n", mask);
	if (!parser(line, mask))
	{
		(*status) = 1;
		free(mask);
		return (0);
	}
	handle_semicolons(line, mask, env, status);
	free(mask);
	return (1);
}

int main(int argc, char **argv, char **env) {
	//char *line = "kek\\''";
	//char *line = "kek' okj\\hf''\\$kekehf\\'lol";
	int status;

	(void)argc;
	(void)argv;
	char line[] = "cat < kek";
	if (!parse_n_execute(line, env, &status))
		return (0);
}