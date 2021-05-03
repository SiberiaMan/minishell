# include "tokenizer.h"

char	*get_path(t_line_n_mask *l_n_m, t_token *token)
{
	char	*after_equal;
	char	*ptr_path;
	size_t	j;
	size_t	i;

	j = -1;
	i = 0;
	while (l_n_m->env[j + 1])
		if (!ft_strncmp_env("PATH", l_n_m->env[++j], 4))
			break ;
	ptr_path = l_n_m->env[j];
	after_equal = (char*)malloc(sizeof(char) * get_cnt_after_equal(ptr_path)
			+ 1);
	if (!after_equal)
		free_token_n_structure_exit(token, l_n_m);
	j = 0;
	while (ptr_path[j++] != '=')
		;
	while (i < ft_strlen(ptr_path))
		after_equal[i++] = ptr_path[j++];
	after_equal[i] = '\0';
	return (after_equal);
}

static void	free_path(char **path)
{
	size_t	i;

	i = 0;
	while(path[i])
		free(path[i++]);
	free(path);
}

size_t check_slash(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
		if (line[i++] == '/')
			return (1);
	return (0);
}

static size_t	is_dir(t_line_n_mask *l_n_m, char *line, char **path)
{
	DIR	*dir;
	char *is_a_directory;
	char *cmd_not_found;

	free_path(path);
	is_a_directory = ": is a directory\n";
	cmd_not_found = ": command not found\n";
	dir = opendir(line);
	if (dir)
	{
		write(2, line, ft_strlen(line));
		write(2, is_a_directory, ft_strlen(is_a_directory));
		l_n_m->status = 126;
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

static size_t	change_cmd(char **path, size_t i, t_token *token,
t_line_n_mask *l_n_m)
{
	char	*temp_ptr;
	char	*new_path;
	size_t	j;

	j = 0;
	new_path = ft_strjoin(path[i], "/");
	if (!new_path)
	{
		free_path(path);
		free_token_n_structure_exit(token, l_n_m);
	}
	temp_ptr = new_path;
	new_path = ft_strjoin(new_path, token->args[0]);
	if (!new_path)
	{
		free(temp_ptr);
		free_path(path);
		free_token_n_structure_exit(token, l_n_m);
	}
	free_path(path);
	free(temp_ptr);
	free(token->args[0]);
	token->args[0] = new_path;
	//printf("%s\n", new_path);
	return (1);
}

size_t	check_cmd(t_line_n_mask *l_n_m, t_token *token, size_t i)
{
	char			**path;
	DIR				*dir;
	struct dirent	*entry;
	size_t			j;

	j = 0;
	handle_cmd(l_n_m, token, i);
	if (token->args[0])
	{
		path = ft_split(get_path(l_n_m, token), ':');
		while (path[j])
		{
			dir = opendir(path[j]);
			if (dir)
			{
				entry = readdir(dir);
				while (entry != 0)
				{
					if (!(ft_strncmp_cmd(token->args[0], entry->d_name,
										 ft_strlen
												 (entry->d_name))))
						return (change_cmd(path, j, token, l_n_m));
					entry = readdir(dir);
				}
				closedir(dir);
			}
			j++;
		}
		return (is_dir(l_n_m, token->args[0], path));
	}
	return (0);
}