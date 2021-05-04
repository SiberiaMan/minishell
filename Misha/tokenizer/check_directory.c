#include "tokenizer.h"

static size_t	check_slash(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
		if (line[i++] == '/')
			return (1);
	return (0);
}

size_t	is_dir(t_line_n_mask *l_n_m, char *line, char **path)
{
	DIR		*dir;
	char	*is_a_directory;
	char	*cmd_not_found;

	free_path(path);
	is_a_directory = ": is a directory\n";
	cmd_not_found = ": command not found\n";
	dir = opendir(line);
	if (check_slash(line) && dir)
	{
		write(2, line, ft_strlen(line));
		write(2, is_a_directory, ft_strlen(is_a_directory));
		l_n_m->status = 126;
		closedir(dir);
		return (0);
	}
	else if (!check_slash(line))
	{
		write(2, line, ft_strlen(line));
		write(2, cmd_not_found, ft_strlen(cmd_not_found));
		l_n_m->status = 127;
		return (0);
	}
	return (1);
}
