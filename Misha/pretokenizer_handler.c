#include "minishell.h"

t_token tokenizer(t_line_n_mask l_n_m, t_pipes_n_pids p_n_pds, size_t *i,
int j)
{
	t_token temp;

	if (j == 0)
		temp.pipe_from = 0;
	if (j == p_n_pds.cnt_pipes)
		temp.pipe_to = 0;

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
	while (j < p_n_pds.cnt_pipes + 1)
	{
		temp_cmd = tokenizer(l_n_m, p_n_pds, &i, j);
		if (j == p_n_pds.cnt_pipes)
		{

		}
	}
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
			handle_pipes(l_n_m, env, j, status);
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
	char line[] = "cat -e | ls -la";
	if (!parse_n_execute(line, env, &status))
		return (0);
}