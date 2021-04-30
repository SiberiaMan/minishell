#include "tokenizer.h"

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
		env[i++] = l_n_m.line[(*start)++];
	env[i] = '\0';
	j = 0;
	while (l_n_m.env[j])
	{
		if (!(ft_strncmp(env, l_n_m.env[j], ft_strlen(l_n_m.env[j]))))
		{
			free(env);
			return (get_cnt_after_equal(l_n_m.env[j]));
		}
		j++;
	}
	free(env);
	return (0);
}

static size_t get_cnt_status(int status)
{
	char	*line;
	size_t 	cnt;

	line = ft_itoa(status);
	///if (!line)
		///exit
	cnt = ft_strlen(line);
	free(line);
	return (cnt);
}

static size_t get_cnt_dollar(t_line_n_mask l_n_m, size_t *start)
{
	size_t 	j;

	(*start)++;
	j = *start;
	if (!l_n_m.mask[j] || (!ft_isalpha(l_n_m.line[j])
	&& l_n_m.line[j] != '_' && l_n_m.line[j] != '?'))
	{
		(*start)++;
		return (1);
	}
	if (l_n_m.line[j] == '?')
		return (get_cnt_status(l_n_m.status));
	while (l_n_m.line[j] && (ft_isalpha(l_n_m.line[j]) || l_n_m.line[j] == '_'))
		j++;
	return (get_cnt_env(l_n_m, start, j)); // cnt for env var
}

static size_t condition(t_line_n_mask l_n_m, size_t start)
{
	if (l_n_m.line[start] && ((l_n_m.mask[start] == '1'
	&& !(l_n_m.mask[start] == '1' && l_n_m.line[start] == ' '))
	|| (l_n_m.line[start] == '$') || (l_n_m.mask[start] == UNUSED_BACKSLASH)
	|| (l_n_m.mask[start] == OPEN_QUOTE) || (l_n_m.mask[start] == CLOSE_QUOTE)
	|| (l_n_m.mask[start] == SPACE_VISIBLE)))
		return (1);
	return (0);
}

static size_t get_cnt_redirect(t_line_n_mask l_n_m, size_t start)
{
	size_t	cnt;

	cnt = 0;
	while ((l_n_m.line[start] == ' ' && l_n_m.mask[start] == '1')
	|| (l_n_m.mask[start] == UNUSED_BACKSLASH))
		start++;
	while (condition(l_n_m, start))
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
	env_lvalue = (char*)malloc(sizeof(char) * cnt + 1);
	///if (!env_lvalue)
		/// exit
	while (*start < j)
		env_lvalue[i++] = l_n_m.line[(*start)++];
	env_lvalue[i] = '\0';
	j = 0;
	while (l_n_m.env[j])
	{
		if (!(ft_strncmp(l_n_m.env[j], env_lvalue, ft_strlen(l_n_m.env[j]))))
		{
			free(env_lvalue);
			return (get_env_rvalue(l_n_m.env[j]));
		}
		j++;
	}
	free(env_lvalue);
	return (ft_strdup("")); ///TODO
}

static void	append_line(char *line, char *env, size_t *i)
{
	size_t j;

	j = 0;
	while (env[j])
		line[(*i)++] = env[j++];
	free(env);
}
// TODO start++ > limits

static void	handle_string_question(t_line_n_mask l_n_m, char *line, size_t *i)
{
	char	*str;
	size_t	len;
	size_t	j;

	str = ft_itoa(l_n_m.status);
	j = 0;
	len = ft_strlen(str);
	///if (!str)
		///exit
	while (j < len)
		line[(*i)++] = str[j++];
	free(str);
}

static void	handle_string_dollar(t_line_n_mask l_n_m, char *line,
size_t *start, size_t *i)
{
	size_t	j;
	char 	*env;

	(*start)++;
	j = *start;
	if (!l_n_m.mask[*start] || (!ft_isalpha(l_n_m.line[j])
	&& l_n_m.line[j] != '_' && l_n_m.line[j] != '?'))
	{
		line[(*i)++] = '$';
		(*start)++;
		return ;
	}
	if (l_n_m.line[j] == '?')
	{
		handle_string_question(l_n_m, line, i);
		(*start)++;
		return ;
	}
	while (l_n_m.line[j] && (ft_isalpha(l_n_m.line[j]) || l_n_m.line[j] == '_'))
		j++;
	env = get_env_string(l_n_m, start, j);
	append_line(line, env, i);
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
	while (condition(l_n_m, start))
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

int	redirect_error(t_token *token, t_line_n_mask *l_n_m)
{
	DIR	*dir;
	char *not_file_error;
	char *is_a_directory;

	is_a_directory = ": is a directory\n";
	not_file_error = ": No such file or directory\n";
	if (token->line)
	{
		dir = opendir(token->line);
		if (dir)
		{
			token->status = 1;
			write(2, token->line, ft_strlen(token->line));
			write(2, is_a_directory, ft_strlen(is_a_directory));
			free(token->line);
			token->line = 0;
			return (0);
		}
	}
	if (token->line && (token->fd_from < 0 || token->fd_to < 0))
	{
		if (token->fd_from < 0)
			token->fd_from = 0;
		if (token->fd_to < 0)
			token->fd_to = 0;
		l_n_m->status = 1;
		write(2, token->line, ft_strlen(token->line));
		write(2, not_file_error, ft_strlen(not_file_error)); ///status?
		free(token->line);
		token->line = 0;
		return (0);
	}
	return (1);
}

static size_t	condition_redirects_1(t_line_n_mask l_n_m, size_t i, char c)
{
	if (l_n_m.line[i] == c && l_n_m.mask[i] == SPEC_SYMBOL
	&& l_n_m.line[i + 1] != c)
		return (1);
	return (0);
}

static size_t	condition_redirects_2(t_line_n_mask l_n_m, size_t i, char c)
{
	if (l_n_m.line[i] == c && l_n_m.mask[i] == SPEC_SYMBOL
	&& l_n_m.line[i + 1] == c && l_n_m.mask[i + 1] == SPEC_SYMBOL)
		return (1);
	return (0);
}

static size_t handle_redirects(t_line_n_mask l_n_m, t_token *token, size_t i)
{
	while (l_n_m.line[i] && !(l_n_m.line[i] == '|' && l_n_m.mask[i] ==
	SPEC_SYMBOL) && (l_n_m.mask[i] != CURRENT_SPLIT))
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
			| O_CREAT | O_TRUNC, S_IREAD | S_IWRITE | S_IRGRP | S_IROTH);
		else if (condition_redirects_2(l_n_m, i, '>'))
		{
			token->fd_to = open(get_redir(l_n_m, i + 2, &(token->line)),
			O_RDWR | O_APPEND | O_CREAT, S_IREAD | S_IWRITE | S_IRGRP |
			S_IROTH);
			i++;
		}
		if (!redirect_error(token, &l_n_m))
			return (0);
		i++;
	}
	return (1);
}

static size_t	condition_cmd_limits(t_line_n_mask l_n_m, size_t i)
{
	if (l_n_m.line[i] && !(l_n_m.line[i] == '|'
	&& l_n_m.mask[i] == SPEC_SYMBOL) && (l_n_m.mask[i] != CURRENT_SPLIT))
		return (1);
	return (0);
}

static void	get_cnt_to_next_arg(t_line_n_mask l_n_m, size_t *i)
{
	if (l_n_m.mask[*i] == OPEN_QUOTE)
		(*i)++;
	while (condition_cmd_limits(l_n_m, *i)
	&& !(l_n_m.line[*i] == ' ' && l_n_m.mask[*i] == '1')
	&& !(l_n_m.mask[*i] == SPEC_SYMBOL && l_n_m.line[*i] != '$')
	&& l_n_m.mask[*i] != CLOSE_QUOTE)
		(*i)++;
}

static size_t	get_cnt_cmds(t_line_n_mask l_n_m, t_token *token, size_t i)
{
	size_t cnt;

	cnt = 0;
	while (condition_cmd_limits(l_n_m, i))
	{
		if (l_n_m.mask[i] == UNUSED_BACKSLASH
		|| l_n_m.mask[i] == CLOSE_QUOTE || l_n_m.mask[i] == UNUSED_SYMBOL
		|| (l_n_m.mask[i] == '1' && l_n_m.line[i] == ' ')
		|| (l_n_m.mask[i] == SPEC_SYMBOL && l_n_m.line[i] != '$'))
			i++;
		else if ((!(l_n_m.line[i] == ' ' && l_n_m.mask[i] == '1')
		&& !(l_n_m.mask[i] == SPEC_SYMBOL && l_n_m.line[i] != '$'))
		|| l_n_m.mask[i] == OPEN_QUOTE)
		{
			get_cnt_to_next_arg(l_n_m, &i);
			cnt++;
		}
	}
	return (cnt);
}

static void	assign_cmd(t_line_n_mask l_n_m, char **line, size_t *i, size_t j)
{
	size_t	k;

	k = 0;
	while (*i < j)
		if (l_n_m.mask[*i] == SPEC_SYMBOL && l_n_m.line[*i] == '$')
			handle_string_dollar(l_n_m, *line, i, &k);
		else if (l_n_m.mask[(*i)] != UNUSED_BACKSLASH
		&& l_n_m.mask[(*i)] != OPEN_QUOTE && l_n_m.mask[(*i)] != CLOSE_QUOTE)
			(*line)[k++] = l_n_m.line[(*i)++];
		else
			(*i)++;
	(*line)[k] = '\0';
}

static void get_size_to_next_arg(t_line_n_mask l_n_m, size_t *i,
size_t *cnt_symbols)
{
	if (l_n_m.mask[*i] == OPEN_QUOTE)
		(*i)++;
	*cnt_symbols = 0;
	while (condition_cmd_limits(l_n_m, *i)
	&& !(l_n_m.line[*i] == ' ' && l_n_m.mask[*i] == '1')
	&& !(l_n_m.mask[*i] == SPEC_SYMBOL && l_n_m.line[*i] != '$'))
		if (l_n_m.line[*i] == '$')
			(*cnt_symbols) += get_cnt_dollar(l_n_m, i);
		else if (l_n_m.mask[*i] != UNUSED_BACKSLASH
		&& l_n_m.mask[*i] != OPEN_QUOTE && l_n_m.mask[*i] != CLOSE_QUOTE)
		{
			(*cnt_symbols)++;
			(*i)++;
		}
		else
			(*i)++;
}

static size_t	handle_cmd_condition(t_line_n_mask l_n_m, size_t i)
{
	if (l_n_m.mask[i] == UNUSED_BACKSLASH
	|| l_n_m.mask[i] == CLOSE_QUOTE || l_n_m.mask[i] == UNUSED_SYMBOL
	|| (l_n_m.mask[i] == '1' && l_n_m.line[i] == ' ')
	|| (l_n_m.mask[i] == SPEC_SYMBOL && l_n_m.line[i] != '$'))
		return (1);
	return (0);
}

static void	handle_cmd(t_line_n_mask l_n_m, t_token *token, size_t i)
{
	size_t	cnt;
	size_t	j_end;
	size_t 	k;
	size_t	cnt_symbols;

	k = 0;
	j_end = 0;
	cnt = get_cnt_cmds(l_n_m, token, i);
	token->args = (char**)malloc(sizeof(char*) * cnt + 1);
	///if (!token->args)
		///exit
	while (k < cnt && condition_cmd_limits(l_n_m, i))
		if (handle_cmd_condition(l_n_m, i))
			i++;
		else if ((!(l_n_m.line[i] == ' ' && l_n_m.mask[i] == '1')
		&& !(l_n_m.mask[i] == SPEC_SYMBOL && l_n_m.line[i] != '$'))
		|| (l_n_m.mask[i] == OPEN_QUOTE))
		{
			j_end = i;
			get_size_to_next_arg(l_n_m, &j_end, &cnt_symbols);
			(token->args)[k] = (char*)malloc(sizeof(char) * cnt_symbols + 1);
			///if (!(token->args)[k])
				///exit
			assign_cmd(l_n_m, &((token->args)[k++]), &i, j_end);
		}
	token->args[k] = 0;
}

static size_t	kernel(t_line_n_mask l_n_m, size_t i, int *status) /// status
// handle
{
	size_t	j;
	t_token	temp_cmd;

	j = 0;
	l_n_m.status = 8475; /// status init
	temp_cmd = token_init();
	l_n_m.free_line = &(temp_cmd.line);
	if (!handle_redirects(l_n_m, &temp_cmd, i))
		printf("stop this pipe and go to next pipe\n");
		/// next pipe
	printf("%s\n", l_n_m.mask);
	if (temp_cmd.line)
		free(temp_cmd.line);
	handle_cmd(l_n_m, &temp_cmd, i);
	while (temp_cmd.args[j])
		printf("%s\n",temp_cmd.args[j++]);
//	printf("kek\n");
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
	size_t 			start;

	start = i;
	l_n_m.cnt_pipes = 0;
	while (l_n_m.line[i] && l_n_m.mask[i] != CURRENT_SPLIT)
	{
		if (l_n_m.line[i] == '|' && l_n_m.mask[i] == SPEC_SYMBOL)
			l_n_m.cnt_pipes++;
		i++;
	}
	l_n_m.pipes = (int**)malloc(sizeof(int[2]) * l_n_m.cnt_pipes);
	if (!l_n_m.pipes) // exit program + status ?
		return (0);
	l_n_m.pids = (int*)malloc(sizeof(int) * l_n_m.cnt_pipes + 1);
	if (!l_n_m.pids) // exit program + status ?
	{
		free(l_n_m.pipes);
		return (0);
	}
	i = start;
	kernel(l_n_m, i, status);
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
	/// exit
	printf("%s\n", line);
	printf("%s\n", mask);
	if (!parser(line, mask))
	{
		(*status) = 1;
		free(mask); //// free struct
		return (0);
	}
	char *kek = (char*)malloc(sizeof(char) * 5000);
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
	char line[] = "echo \"\\$PWD       \" rgjjghr gj jgj   g5jrjg ";
	if (!parse_n_execute(line, env, &status))
		return (0);
}