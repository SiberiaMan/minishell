#include "executing.h"

static size_t handle_pipes(t_line_n_mask *l_n_m, size_t i)
{
	size_t 	start;

	start = i;
	l_n_m->cnt_pipes = 0;
	while (l_n_m->line[i] && l_n_m->mask[i] != CURRENT_SPLIT)
	{
		if (l_n_m->line[i] == '|' && l_n_m->mask[i] == SPEC_SYMBOL)
			l_n_m->cnt_pipes++;
		i++;
	}
	l_n_m->pipes = (int**)malloc(sizeof(int*) * (l_n_m->cnt_pipes + 1));
	if (!l_n_m->pipes)
		free_and_exit(l_n_m);
	malloc_pipes(l_n_m);
	l_n_m->pids = (int*)malloc(sizeof(int) * l_n_m->cnt_pipes + 1);
	if (!l_n_m->pids)
		free_and_exit(l_n_m);
	i = start;
	kernel_start(l_n_m, i);
	l_n_m->gnl->status = l_n_m->status;
	free_kernel(l_n_m);
	return (0);
}

void	handle_semicolons(t_gnl *gnl, char *mask, char ***env)
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
	i = j;
	while (l_n_m.line[i])
	{
		if (!(l_n_m.line[i] == ' ' && mask[i] == '1'))
		{
			handle_pipes(&l_n_m, j);
			break ;
		}
		i++;
	}
}