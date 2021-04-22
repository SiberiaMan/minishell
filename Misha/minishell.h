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

# define SYNTAX_ERR "syntax error near token "
# define CMD_NF		"command not found"

typedef	struct 		s_token
{
	char	*cmd;
	char	**args;
	int		pipe_from;
	int 	pipe_to;
	int 	fd_from;
	int 	fd_to;
}					t_token;

typedef struct 		s_subtoken
{
	int 	cmd;
	int 	cmd_arg;
	int 	outfile;
	int 	infile;
}					t_subtoken;

int		parser(char *line);
void	print_syntax_err(char *err);

#endif //SHELL_MINISHELL_H