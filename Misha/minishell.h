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
#include "parser.h"

# define SYNTAX_ERR "syntax error near token "
# define CMD_NF		"command not found"
# define BACKSLASH  '5' // можно ли заменить на 5 // попробую заменить 2 -> 5
# define FAKE_SPEC_SYMBOL '3' // можно ли заменить на 1 // пока не буду
// менять, чтобы было удобнее смотреть результат // на продакт надо будет
// заменить
# define SPEC_SYMBOL '4'
# define UNUSED_BACKSLASH '5'
# define OPEN_QUOTE '6'
# define CLOSE_QUOTE '7'
# define SPACE_VISIBLE '8'

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

void	print_syntax_err(char *err);
char 	*get_mask_normal(char *line);
char 	*get_mask_real(char *line);
size_t	quotes_handler(char *line, char *mask);

#endif //SHELL_MINISHELL_H
