#include "minishell.h"

static char	*get_normal_form(char **line_splitted_by_space)
{
	char 	*join_str;
	char 	*temp_join_str;
	size_t	i;

	i = 0;
	temp_join_str = 0;
	join_str = "";
	while (line_splitted_by_space[i])
	{
		if (!(join_str = ft_strjoin(join_str, line_splitted_by_space[i++])))
		{
			if (temp_join_str)
				free(temp_join_str);
			return (0);
		}
		if (temp_join_str)
			free(temp_join_str);
		temp_join_str = join_str;
	}
	return (join_str);
}

static char	*get_normal_form_space(char **line_splitted_by_space)
{
	char 	*join_str;
	char 	*temp_join_str;
	size_t	i;

	i = 0;
	temp_join_str = 0;
	join_str = "";
	while (line_splitted_by_space[i])
	{
		if (!(join_str = ft_strjoin_space(join_str, line_splitted_by_space[i++])))
		{
			if (temp_join_str)
				free(temp_join_str);
			return (0);
		}
		if (temp_join_str)
			free(temp_join_str);
		temp_join_str = join_str;
	}
	return (join_str);
}

char	*normal_form(char *line)
{
	char	**line_splitted_by_space;
	char 	*str_normal_form;
	size_t	i;

	i = 0;
	if (!(line_splitted_by_space = ft_split(line, ' ')))
		return (0);
	str_normal_form = get_normal_form(line_splitted_by_space);
	while (line_splitted_by_space[i])
		free(line_splitted_by_space[i++]);
	free(line_splitted_by_space);
	return (str_normal_form);
} // free line ?

char	*normal_space_form(char *line)
{
	char	**line_splitted_by_space;
	char 	*str_normal_space_form;
	size_t	i;

	i = 0;
	if (!(line_splitted_by_space = ft_split(line, ' ')))
		return (0);
	str_normal_space_form = get_normal_form_space(line_splitted_by_space);
	while (line_splitted_by_space[i])
		free(line_splitted_by_space[i++]);
	free(line_splitted_by_space);
	return (str_normal_space_form);
} // free line ?
