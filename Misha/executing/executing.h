#ifndef EXECUTING_H
# define EXECUTING_H

# include "../tokenizer/tokenizer.h"
# include <errno.h>
# include "../builtins/builtins.h"

t_token token_init(void);
void	kernel_start(t_line_n_mask *l_n_m, size_t start);
void	malloc_pipes(t_line_n_mask *l_n_m);
void	free_and_exit(t_line_n_mask *l_n_m);
t_line_n_mask struct_init(char ***env, char *mask, t_gnl *gnl);
void	free_token(t_token *token);
size_t	get_next_pipe(t_line_n_mask *l_n_m, size_t j);
void	kernel(t_line_n_mask *l_n_m, size_t start);
void	handle_semicolons(t_gnl *gnl, char *mask, char ***env);
void	change_io(t_line_n_mask *l_n_m, t_token *token, size_t i);
void	free_kernel(t_line_n_mask *l_n_m);

#endif