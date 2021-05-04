#ifndef SHELL_PARSER_H
#define SHELL_PARSER_H

# include <stdlib.h>
# include <stdio.h>
# include "../minishell_utils/minishell_utils.h"

# define SYNTAX_ERR "syntax error near token "
# define CMD_NF		"command not found"
# define BACKSLASH  '5' // можно ли заменить на 5 // попробую заменить 2 -> 5
# define FAKE_SPEC_SYMBOL '1' // можно ли заменить на 1 // пока не буду
// менять, чтобы было удобнее смотреть результат // на продакт надо будет
// заменить
# define CURRENT_SPLIT '2'
# define SPEC_SYMBOL '4'
# define UNUSED_BACKSLASH '5'
# define OPEN_QUOTE '6'
# define CLOSE_QUOTE '7'
# define SPACE_VISIBLE '8'
# define UNUSED_SYMBOL '0'

int		parser(const char *line, const char *mask);
size_t	redirect_syntax(const char *line, const char *mask, char *c);
void	print_syntax_err(char err);
size_t 	get_mask_normal(char *line, char *mask);
size_t	quotes_handler(char *line, char *mask);

#endif //SHELL_PARSER_H
