#include "builtins.h"

void export_error(char *line)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("':", 2);
	ft_putstr_fd(" not a valid identifier", 2);
}

void	check_line(char *line, char *eqsign, size_t len)
{
	size_t	valid_len;

	valid_len = 0;
	if(*line == '=');
		export_error(eqsign);
	else if (*(eqsign - 1) == ' ')
		export_error(eqsign);
	else if (*(eqsign + 1) == ' ')
	{
		eqsign++;
		while(*eqsign == ' ' && *eqsign != '\0')
			eqsign++;
		if(*eqsign != '\0')
			export_error(eqsign);
	}
}

char	**collect_valid_vars(int count, char **vars, t_line_n_mask *l_n_m, t_token *token)
{
	char	**ptr;
	char	**valid_vars;
	char	*equalsign;
	int		k;

	k = 0;
	ptr = vars;
	valid_vars = (char **)malloc((sizeof(char *) * (count + 1)));
	if (!res)
		free_export(l_n_m, token, NULL, 0);
	while (*ptr)
	{
		equalsign = ft_strchr(*ptr, '=');
		if (equalsign)
		{
			valid_vars[k] = ft_strdup(*ptr);
			if (!valid_vars[k])
				free_export(l_n_m, token, valid_vars, k - 1);
			k++;
		}
		ptr++;
	}
	valid_vars[count] = NULL;
	return (valid_vars);
}

int	count_valid_vars(char **vars)
{
	char	**ptr;
	char	*equalsign;
	int		count;

	count = 0;
	ptr = vars;
	while (*ptr)
	{
		equalsign = ft_strchr(*ptr, '=');
		if (equalsign)
		{
			count++;
			if (check_line(*ptr, equalsign, ft_strlen(*ptr)) == -1)
				return (-1);
		}
		ptr++;
	}
	return (count);
}
