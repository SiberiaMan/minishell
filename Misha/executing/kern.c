#include "executing.h"

t_token token_init(void)
{
	return ((t_token) {
			.args = 0,
			.line = 0,
			.fd_from = 0,
			.fd_to = 1,
	});
}

/*size_t	kernel(t_line_n_mask l_n_m, size_t i, int *status) /// status
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
	}
} */

size_t	get_next_pipe(t_line_n_mask l_n_m, size_t j)
{
	while(l_n_m.line[j] && !(l_n_m.line[j] == '|'
	&& l_n_m.mask[j] == SPEC_SYMBOL))
		j++;
	j++;
	return (j);
}

char	*get_path(t_line_n_mask *l_n_m)
{
	char *after_equal;
	char *ptr_path;
	size_t j;
	size_t i;

	j = -1;
	i = 0;
	while (l_n_m->env[j + 1])
		if (!ft_strncmp("PATH", l_n_m->env[++j], 4))
			break;
	ptr_path = l_n_m->env[j];
	after_equal = (char*)malloc(sizeof(char) * get_cnt_after_equal(ptr_path) + 1);
	//if (!after_equal)
	/// exit
	j = 0;
	while (ptr_path[j++] != '=')
		;
	while (i < ft_strlen(ptr_path))
		after_equal[i++] = ptr_path[j++];
	after_equal[i] = '\0';
	return (after_equal);
}

int is_dir(t_line_n_mask *l_n_m, char *line)
{
	size_t i;
	DIR *dir;

	dir = opendir(line);
	if (dir)
	{
		write(2, "is a directory\n", ft_strlen("is a directory\n"));
		l_n_m->status = 126;
	}
	else
	{
		write(2, "not such file or directory\n", ft_strlen("not such file or "
														   "directory\n"));
		l_n_m->status = 127;
	}
	return (0);
}

int check_cmd(t_line_n_mask *l_n_m, t_token *token)
{
	char **path;
	DIR  *dir;
	struct dirent *entry;
	size_t i;
	char *path_to;

	i = 0;
	path = ft_split(get_path(l_n_m), ':');
	while (path[i])
	{
		dir = opendir(path[i]);
		while ((entry = readdir(dir)) != 0)
		{
			if (!(ft_strncmp(token->args[0], entry->d_name, ft_strlen
			(entry->d_name))))
			{
				path_to = ft_strjoin(path[i], "/");
				path_to = ft_strjoin(path_to, token->args[0]);
				///if (!path_to)
					///exit;
				free(token->args[0]);
				token->args[0] = path_to;
				/// clean path
				return (1);
			}
		}
		closedir(dir);
		i++;
	}
	/// clean path
	return (is_dir(l_n_m, token->args[0]));
}

void kernel(t_line_n_mask l_n_m, size_t start)
{
	t_token token;
	int		fdout;
	int		fdin;
	size_t	j;
	size_t	i;

	j = start;
	i = 0;
	fdout = dup(1); /// handle dup
	fdin = dup(0);
	while (i < l_n_m.cnt_pipes + 1) // num of pids
	{
		token = token_init();
		if (!handle_redirects(l_n_m, &token, j))
		{
			if (token.line)
				free(token.line);
			j = get_next_pipe(l_n_m, j);
			i++;
			continue;
		}
		handle_cmd(l_n_m, &token, j);
		if (!check_cmd(&l_n_m, &token))
		{
			if (token.line)
				free(token.line);
			j = get_next_pipe(l_n_m, j);
			i++;
			continue;
		}
		l_n_m.pids[i] = fork(); /// handle
		if (!l_n_m.pids[i])
		{
			change_io(&l_n_m, token, i, fdout, fdin);
			execve(token.args[0], token.args, l_n_m.env);
			perror("Error:");
			exit(1);
		}
		j = get_next_pipe(l_n_m, j);
		i++;
		///free;
	}
	for (int k = 0; k < l_n_m.cnt_pipes + 1; k++)
	{
		close(l_n_m.pipes[k][0]);
		close(l_n_m.pipes[k][1]);
	}
	i = 0;
	while (i < l_n_m.cnt_pipes + 1 && waitpid(l_n_m.pids[i], &l_n_m.status, 0))
		i++;
}

static size_t handle_pipes(t_line_n_mask l_n_m, size_t i, int *status)
{
	size_t 			start;
	size_t			j;

	start = i;
	j = 0;
	l_n_m.cnt_pipes = 0;
	while (l_n_m.line[i] && l_n_m.mask[i] != CURRENT_SPLIT)
	{
		if (l_n_m.line[i] == '|' && l_n_m.mask[i] == SPEC_SYMBOL)
			l_n_m.cnt_pipes++;
		i++;
	}
	l_n_m.pipes = (int**)malloc(sizeof(int[2]) * (l_n_m.cnt_pipes + 1));
	for (int k = 0; k < l_n_m.cnt_pipes + 1; k++)
		l_n_m.pipes[k] = (int*)malloc(sizeof(int) * 2);
	if (!l_n_m.pipes) // exit program + status ?
		return (0);
	l_n_m.pids = (int*)malloc(sizeof(int) * l_n_m.cnt_pipes + 1);
	if (!l_n_m.pids) // exit program + status ?
	{
		free(l_n_m.pipes);
		return (0);
	}
	while (j < l_n_m.cnt_pipes + 1)
	{
		if (pipe(l_n_m.pipes[j++]) < 0) /// handle error pipe
			printf("error with pipe\n");
	}
	i = start;
	kernel(l_n_m, i);
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
	char line[] = "ls -la > thatfile| cat -e < file| grep kek";
	if (!parse_n_execute(line, env, &status))
		return (0);
}