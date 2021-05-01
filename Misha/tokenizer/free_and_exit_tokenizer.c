#include "tokenizer.h"

void	free_and_exit_tokenizer_cmd(t_token *token, t_line_n_mask *l_n_m,
size_t i)
{
	size_t j;

	j = 0;
	while (j < i)
		free(token->args[j++]);
	free(token->args);
	free_and_exit_tokenizer(l_n_m);
}

void	free_and_exit_tokenizer(t_line_n_mask *l_n_m)
{
	size_t 	j;

	j = 0;
	free_gnl(l_n_m->gnl);
	while (l_n_m->env[j])
		free(l_n_m->env[j++]);
	free (l_n_m->env);
	free (l_n_m->mask);
	if (l_n_m->pids)
		free(l_n_m->pids);
	if (l_n_m->pipes)
		free(l_n_m->pipes);
	if (*(l_n_m->free_line))
		free(*(l_n_m->free_line));
	exit (1);
}