#ifndef EXECUTING_H
# define EXECUTING_H

# include "../minishell.h"
# include "../tokenizer/tokenizer.h"

size_t	kernel(t_line_n_mask l_n_m, size_t i, int *status);
void	handle_semicolons(const char *line, char *mask, char **env,
int *status);

#endif