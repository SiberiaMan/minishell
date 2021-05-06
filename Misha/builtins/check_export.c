#include "builtins.h"

int export_error(char *line)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("':", 2);
	ft_putstr_fd(" not a valid identifier\n", 2);
	return (-1);
}

int	check_line(char *line, char *eqsign)
{
	char *start;

	start = line;
	if(*line == '=')
		return(export_error(eqsign));
	else if (*(eqsign - 1) == ' ')
		return(export_error(eqsign));
	while(*start != '=' && *start != '\0')
	{
		if(!(*start == '_' || ft_isalpha(*start)))
			return(export_error(line));
	}
	return(0);
}

char	**collect_valid_vars(int count, char **vars, t_line_n_mask *l_n_m, t_token *token)
{
	//char *tmp;
	char	**ptr;
	char	**valid_vars;
	char	*equalsign;
	int		k;

	k = 0;
	ptr = vars;
	valid_vars = (char **)malloc((sizeof(char *) * (count + 1)));
	if (!valid_vars)
		free_export(l_n_m, token, NULL, 0);
	while (*ptr)
	{
		equalsign = ft_strchr(*ptr, '=');
		if (equalsign)
		{
			//tmp = *ptr;
			valid_vars[k] = ft_strdup(*ptr);
			if (!valid_vars[k])
				free_export(l_n_m, token, valid_vars, k - 1);
			//free(tmp);
			k++;
		}
		ptr++;
	}
	valid_vars[count] = NULL;
	return (valid_vars);
}

int	count_valid_vars(char **vars)
{
	int		i;
	char	*equalsign;
	int		count;

	count = 0;
	i = 1;
	while (vars[i])
	{
		equalsign = ft_strchr(vars[i], '=');
		if (equalsign)
		{
			if (check_line(vars[i], equalsign) != 0)
				return (-1);
		}
		count++;
		i++;
	}
	return (count);
}