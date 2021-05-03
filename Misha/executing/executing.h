#ifndef EXECUTING_H
# define EXECUTING_H

# include "../tokenizer/tokenizer.h"
# include <errno.h>

void	free_and_exit(t_line_n_mask *l_n_m);
void	kernel(t_line_n_mask *l_n_m, size_t start);
void	handle_semicolons(t_gnl *gnl, char *mask, char **env);
void	change_io(t_line_n_mask *l_n_m, t_token *token, size_t i);
void	free_kernel(t_line_n_mask *l_n_m);

#endif