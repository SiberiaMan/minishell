#include "executing.h"

static void	last_pid(t_line_n_mask *l_n_m, size_t i)
{
	waitpid(l_n_m->pids[i], &l_n_m->status, WUNTRACED);
	if (WIFEXITED(l_n_m->status))
		l_n_m->status = WEXITSTATUS(l_n_m->status);
	else if (WIFSIGNALED(l_n_m->status))
	{
		write(1, "\n", 1);
		l_n_m->status = 128 + WTERMSIG(l_n_m->status);
	}
	else if (WIFSTOPPED(l_n_m->status))
	{
		write(1, "\n", 1);
		l_n_m->status = 128 + WSTOPSIG(l_n_m->status);
	}
}

void	wait_childs(t_line_n_mask *l_n_m)
{
	size_t	i;

	i = 0;
	while (i < l_n_m->cnt_pipes + 1)
	{
		if (l_n_m->pids[i] != -1)
		{
			if (i == l_n_m->cnt_pipes)
				last_pid(l_n_m, i);
			else
				waitpid(l_n_m->pids[i], 0, 0);
		}
		i++;
	}
}
