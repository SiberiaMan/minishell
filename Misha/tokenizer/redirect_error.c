#include "tokenizer.h"

int	redirect_error(t_token *token, t_line_n_mask *l_n_m)
{
	DIR	*dir;
	char *not_file_error;
	char *is_a_directory;

	is_a_directory = ": is a directory\n";
	not_file_error = ": No such file or directory\n";
	if (token->line)
	{
		dir = opendir(token->line);
		if (dir)
		{
			token->status = 1;
			write(2, token->line, ft_strlen(token->line));
			write(2, is_a_directory, ft_strlen(is_a_directory));
			free(token->line);
			token->line = 0;
			return (0);
		}
	}
	if (token->line && (token->fd_from < 0 || token->fd_to < 0))
	{
		if (token->fd_from < 0)
			token->fd_from = 0;
		if (token->fd_to < 0)
			token->fd_to = 0;
		l_n_m->status = 1;
		write(2, token->line, ft_strlen(token->line));
		write(2, not_file_error, ft_strlen(not_file_error)); ///status?
		free(token->line);
		token->line = 0;
		return (0);
	}
	return (1);
}