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

typedef struct 		s_subtoken
{
	int 	cmd;
	int 	cmd_arg;
	int 	outfile;
	int 	infile;
}					t_subtoken;

char 	*get_mask_normal(char *line);
char 	*get_mask_real(char *line);
size_t	quotes_handler(char *line, char *mask);

#endif //SHELL_MINISHELL_H
