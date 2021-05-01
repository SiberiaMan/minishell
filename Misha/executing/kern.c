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

size_t	kernel(t_line_n_mask *l_n_m, size_t i) /// status
// handle
{
	size_t	j;
	t_token	temp_cmd;

	j = 0;
	l_n_m->status = 8475; /// status init
	temp_cmd = token_init();
	l_n_m->free_line = &(temp_cmd.line);
	if (!handle_redirects(l_n_m, &temp_cmd, i))
		printf("stop this pipe and go to next pipe\n");
	/// next pipe
	//printf("%s\n", l_n_m.mask);
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

static size_t handle_pipes(t_line_n_mask *l_n_m, size_t i)
{
	size_t 			start;

	start = i;
	while (l_n_m->line[i] && l_n_m->mask[i] != CURRENT_SPLIT)
	{
		if (l_n_m->line[i] == '|' && l_n_m->mask[i] == SPEC_SYMBOL)
			l_n_m->cnt_pipes++;
		i++;
	}
	l_n_m->pipes = (int**)malloc(sizeof(int[2]) * l_n_m->cnt_pipes);
	if (!l_n_m->pipes) // exit program + status ?
		free_and_exit(l_n_m);
	l_n_m->pids = (int*)malloc(sizeof(int) * l_n_m->cnt_pipes + 1);
	if (!l_n_m->pids) // exit program + status ?
		free_and_exit(l_n_m);
	i = start;
	kernel(l_n_m, i);
	return (0);
}

static t_line_n_mask struct_init(char **env, char *mask, t_gnl *gnl)
{
	return (t_line_n_mask) {
		.line = gnl->history->line,
		.env = env,
		.mask = mask,
		.free_line = 0,
		.pipes = 0,
		.pids = 0,
		.status = gnl->status,
		.cnt_pipes = 0,
		.gnl = gnl
	};
}

void	handle_semicolons(t_gnl *gnl, char *mask, char **env)
{
	size_t			i;
	size_t			j;
	t_line_n_mask	l_n_m;

	i = 0;
	j = 0;
	l_n_m = struct_init(env, mask, gnl);
	while (l_n_m.line[i])
	{
		if (l_n_m.line[i] == ';' && mask[i] == SPEC_SYMBOL)
		{
			mask[i] = CURRENT_SPLIT;
			handle_pipes(&l_n_m, j);
			j = i + 1;
		}
		i++;
	}
	handle_pipes(&l_n_m, j);
}