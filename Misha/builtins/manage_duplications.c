#include "builtins.h"

int	check_duplication(char *v, char **envp)
{
	int		flag;
	int		i;
	char	*e;
	char	*ptr;

	i = 0;
	flag = 0;
	while (*envp && flag == 0)
	{
		e = *envp;
		ptr = *envp;
		while (v[i] == e[i] && v[i] != '=' && e[i] != '=')
			i++;
		if (v[i] == '=' && e[i] == '=')
		{
			*envp = ft_strdup(v);
			free(ptr);
			free(v);
			i = 0;
			flag = 1;
		}
		envp++;
	}
	return (flag);
}

char	**manage_duplication(char **p_vars, char **p_envp, t_line_n_mask *l_n_m, t_token *token)
{
	char	**vars;
	char	**envp;
	char	*v;
	char	**new_envp;

	vars = p_vars;
	envp = p_envp;
	while (*vars)
	{
		v = *vars;
		if (check_duplication(v, envp) == 0)
		{
			new_envp = export_one_var(v, envp, l_n_m, token); ///маллок
			free_vars(envp, count_vars(envp) - 1 );
			envp = new_envp;
		}
		vars++;
	}
	return (envp);
}
