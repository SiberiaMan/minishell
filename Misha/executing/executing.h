#ifndef EXECUTING_H
# define EXECUTING_H

# include "../tokenizer/tokenizer.h"

void	free_and_exit(t_line_n_mask *l_n_m);
size_t	kernel(t_line_n_mask *l_n_m, size_t i);
void	handle_semicolons(t_gnl *gnl, char *mask, char **env);

#endif