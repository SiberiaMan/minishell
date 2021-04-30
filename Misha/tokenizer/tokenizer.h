#ifndef TOKENIZER_H
# define TOKENIZER_H

#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include "../history.h"
#include "../parser/parser.h"
#include <fcntl.h>

typedef struct	s_line_n_mask
{
	const char	*line;
	char		**env;
	char		*mask;
	char		*history;
	int			status;
	char		**free_line;
	int			**pipes;
	int 		*pids;
	size_t		cnt_pipes;
}				t_line_n_mask;

typedef	struct 		s_token
{
	char	**args;
	char	*line;
	int		pipe_from;
	int 	pipe_to;
	int 	fd_from;
	int 	fd_to;
	int 	is_from;
	int 	is_to;
	int 	status;
}					t_token;

size_t handle_redirects(t_line_n_mask l_n_m, t_token *token, size_t i);
size_t get_cnt_dollar(t_line_n_mask l_n_m, size_t *start);
size_t 	get_cnt_after_equal(char *line);
void	handle_string_dollar(t_line_n_mask l_n_m, char *line,
size_t *start, size_t *i);
size_t	condition_redirects_1(t_line_n_mask l_n_m, size_t i, char c);
size_t	condition_redirects_2(t_line_n_mask l_n_m, size_t i, char c);
size_t	condition_redirects3(t_line_n_mask l_n_m, size_t start);
int		redirect_error(t_token *token, t_line_n_mask *l_n_m);
void	handle_cmd(t_line_n_mask l_n_m, t_token *token, size_t i);
size_t	condition_cmd_limits(t_line_n_mask l_n_m, size_t i);
size_t	handle_cmd_condition(t_line_n_mask l_n_m, size_t i);

#endif