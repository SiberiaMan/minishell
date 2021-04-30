#include "executing.h"

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

size_t	kernel(t_line_n_mask l_n_m, size_t i, int *status) /// status
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

void	handle_semicolons(const char *line, char *mask, char **env,
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
/*

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

int start_cmd(t_gnl *gnl) {
	//char *line = "kek\\''";
	//char *line = "kek' okj\\hf''\\$kekehf\\'lol";
	int status;

	char line[] = " echo $PWD $PWD $BIN $USER dchani   \\$P\\A\\T\\H  | ls -la";
	if (!parse_n_execute(line, env, &status))
		return (0);
} */