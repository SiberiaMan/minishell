#ifndef SHELL_MINISHELL_H
#define SHELL_MINISHELL_H

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "history.h"
#include "parser/parser.h"

typedef struct	s_line_n_mask
{
	const char	*line;
	char		**env;
	char		*mask;
}				t_line_n_mask;

typedef struct	s_pipes_n_pids
{
	int		**pipes;
	int 	*pids;
	size_t	cnt_pipes;
}				t_pipes_n_pids;

typedef	struct 		s_token
{
	char	**args;
	int		pipe_from;
	int 	pipe_to;
	int 	fd_from;
	int 	fd_to;
	int 	is_from;
	int 	is_to;
}					t_token;

typedef struct 		s_subtoken
{
	int 	cmd;
	int 	cmd_arg;
	int 	outfile;
	int 	infile;
}					t_subtoken;

void	print_syntax_err(char *err);
char 	*get_mask_normal(char *line);
char 	*get_mask_real(char *line);
size_t	quotes_handler(char *line, char *mask);

#endif //SHELL_MINISHELL_H
