#include "executing.h"

t_token token_init(void)
{
	return ((t_token) {
			.args = 0,
			.line = 0,
			.fd_from = 0,
			.fd_to = 1
	});
}

void	free_token(t_token *token)
{
	size_t	i;

	i = 0;
	if (token->args)
	{
		while(token->args[i])
			free(token->args[i++]);
		free(token->args);
	}
	if (token->line)
		free(token->line);
}

size_t	get_next_pipe(t_line_n_mask *l_n_m, size_t j)
{
	while (l_n_m->line[j] && !(l_n_m->line[j] == '|'
							   && l_n_m->mask[j] == SPEC_SYMBOL))
		j++;
	j++;
	return (j);
}

void	child_process(t_line_n_mask *l_n_m, t_token token, size_t i)
{
	change_io(l_n_m, &token, i);
	execve(token.args[0], token.args, *l_n_m->env);
	perror("Error: ");
	exit (1);
}

void	kernel(t_line_n_mask *l_n_m, size_t start)
{
	t_token	token;
	size_t	j;
	size_t	i;

	j = start;
	i = 0;
	while (i < l_n_m->cnt_pipes + 1)
	{
		token = token_init();
		if (handle_redirects(l_n_m, &token, j)
		&& (check_cmd(l_n_m, &token, j)))
		{
			if (check_builtins(token.args[0]))
				choose_builtin(l_n_m, &token, i);
			else
			{
				l_n_m->pids[i] = fork();
				if (l_n_m->pids[i] < 0)
					free_token_n_structure_exit(&token, l_n_m);
				if (!l_n_m->pids[i])
					child_process(l_n_m, token, i);
			}
		}
		free_token(&token);
		j = get_next_pipe(l_n_m, j);
		i++;
	}
}

void	kernel_start(t_line_n_mask *l_n_m, size_t start)
{
	size_t	i;

	i = 0;
	kernel(l_n_m, start);
	while (i < l_n_m->cnt_pipes + 1)
	{
		close(l_n_m->pipes[i][0]);
		close(l_n_m->pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < l_n_m->cnt_pipes + 1 && waitpid(l_n_m->pids[i],
	&l_n_m->status, 0))
		i++;
}

static void	malloc_pipes(t_line_n_mask *l_n_m)
{
	size_t	i;
	size_t 	j;

	i = 0;
	while (i < l_n_m->cnt_pipes + 1)
	{
		l_n_m->pipes[i] = (int*)malloc(sizeof(int) * 2);
		if (!l_n_m->pipes[i])
		{
			j = 0;
			while (j < i)
				free(l_n_m->pipes[j++]);
			free_and_exit(l_n_m);
		}
		if (pipe(l_n_m->pipes[i]) < 0)
		{
			j = 0;
			while (j < i)
				free(l_n_m->pipes[j++]);
			free_and_exit(l_n_m);
		}
		i++;
	}
}

static size_t handle_pipes(t_line_n_mask *l_n_m, size_t i)
{
	size_t 	start;
	size_t	j;

	start = i;
	j = 0;
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
	free_kernel(l_n_m);
	return (0);
}

static t_line_n_mask struct_init(char ***env, char *mask, t_gnl *gnl)
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