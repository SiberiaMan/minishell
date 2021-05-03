#ifndef EXECUTING_H
# define EXECUTING_H

# include "../minishell.h"
# include "../tokenizer/tokenizer.h"

void change_io(t_line_n_mask *l_n_m, t_token token, size_t i, int fdout, int
fdin);

#endif