#include "builtins.h"

int check_entry(char *v, char **envp, int count)
{
	int len;
	char *e;
	int i;
	int c;

	i = 0;
	c = 0;
	len = ft_strlen(v);
	while(c < count)
	{
		e = envp[c];
		if (e)
		{
			while (e[i] == v[i] && i < len)
				i++;
			if (e[i] == '=')
			{
				return (c);
			}
		}
		c++;
	}
	return(0);
}

char **unset(char **vars, char **envp, t_line_n_mask *l_n_m, t_token *token)
{
	int count;
	int i;
	int del;
	char **res;
	int j = 0;

	count = count_vars(envp);
	del = 0;
	while(*vars)
	{
		i = check_entry(*vars, envp, count);
		if(i >= 0)
		{
			del++;
			free(envp[i]);
			envp[i] = NULL;
		}
		vars++;
	}
	res = (char **)malloc((sizeof(char *) * count - del + 1 ));
	if (!res)
		free_export(l_n_m, token, NULL, 0);
	i = 0;
	while(i < count)
	{
		if (envp[i] != NULL)
		{
			res[j] = ft_strdup(envp[i]);
			if (!res[j])
				free_export(l_n_m, token, res, j - 1);
			free(envp[i]);
			j++;
		}
		i++;
	}
	res[j] = NULL;
	free(envp);
	return(res);
}

int	ft_unset(t_line_n_mask *l_n_m, t_token *token)
{
	char **vars;
	char **envp;

	vars = token->args;
	envp = *l_n_m->env;

	*l_n_m->env = unset(vars, envp, l_n_m, token);
	return(0);
}

