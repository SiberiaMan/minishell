#ifndef SHELL_PARSER_H
#define SHELL_PARSER_H

# include <stdlib.h>
# include <stdio.h>
# include "history.h"

int		parser(const char *line, const char *mask);
void	print_syntax_err(char *err);
char 	*get_mask_normal(char *line);
char 	*get_mask_real(char *line);
size_t	quotes_handler(char *line, char *mask);
char 	**split_symbols(const char *line, const char *mask, char c);

#endif //SHELL_PARSER_H
