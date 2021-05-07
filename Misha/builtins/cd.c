#include "builtins.h"
#include "errno.h"

int cd_error(char *path, int res)
{
	printf("minishell: %s: %s\n", path, strerror(errno));
	return(1);
}

int change_directory(char *path)
{
	int res;

	res = chdir(path);
	return (res);
}

char *return_env(char *env, char **envp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(envp[i])
	{
		if(!ft_strncmp(envp[i], env, ft_strlen(env)))
		{
			while (envp[i][j] != '=' && envp[i][j] != '\0')
				j++;
			return(&envp[i][j + 1]);
		}
		i++;
	}
	return(NULL);
}

int change_to_home_dir(char **envp)
{
	char *path;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "HOME=", 5))
		{
			path = *envp + 5;
		}
		envp++;
	}
	return (change_directory(path));
}

int export_pwd_oldpwd(char *pwd, char *oldpwd, t_token *token, t_line_n_mask
		*l_n_m)
{
	char **ex;
	char **new_envp;

	ex = (char **)malloc((sizeof(char *) * 4));
	if (!ex)
	{
		free(pwd);
		free(oldpwd);
		free_token_n_structure_exit(token, l_n_m);
	}
	ex[0] = ft_strdup("export");
	if(!ex[0])
		free(ex);
	ex[1] = ft_strdup(pwd);
	if(!ex[1])
		free_vars(ex, 0);
	ex[2] = ft_strdup(oldpwd);
	if(!ex[2])
		free_vars(ex, 1);
	ex[3] = NULL;
	new_envp = manage_duplication(ex, *l_n_m->env, l_n_m, token);
	*l_n_m->env = new_envp;
	free(pwd);
	free(oldpwd);
	free_vars(ex, count_vars(ex) - 1);
	return(0);
}

int join_oldpwd(t_token *token, t_line_n_mask *l_n_m)
{
	char *pwd;
	char *oldpwd;
	char *tmp;

	pwd = return_new_pwd();
	tmp = pwd;
	pwd = ft_strjoin("PWD=", pwd);
	if(!pwd)
	{
		free(tmp);
		free_token_n_structure_exit(token, l_n_m);
	}
	free(tmp);
	oldpwd = ft_strdup("OLDPWD=");
	if (!oldpwd)
		free_token_n_structure_exit(token, l_n_m);
	tmp = oldpwd;
	oldpwd = ft_strjoin(oldpwd, return_env("PWD", *l_n_m->env));
	if (!oldpwd)
	{
		free(tmp);
		free_token_n_structure_exit(token, l_n_m);
	}
	free(tmp);
	return(export_pwd_oldpwd(pwd, oldpwd, token, l_n_m));
}

int absolute_or_relative_path(char **args, t_token *token, t_line_n_mask *l_n_m)
{
	int res;
	int i;
	char *ptr;
	char *path;
	(void)(token);
	(void)(l_n_m);
	path = ft_calloc(1, 1);
	if(!path)
		free_token_n_structure_exit(token, l_n_m);
	i = 1;
	if (args[1] == NULL)
		res = change_to_home_dir(*l_n_m->env);
	else
	{
		while (args[i])
		{
			ptr = path;
			path = ft_strjoin(path, args[i]);
			if(!path)
			{
				free_token_n_structure_exit(token, l_n_m);
				free(ptr);
			}
			free(ptr);
			i++;
		}
		res = change_directory(path);
	}
	if (res == 0)
	{
		free(path);
		return (join_oldpwd(token, l_n_m));
	}
	else
		return(cd_error(path, res));
}

int ft_cd(t_token *token, t_line_n_mask *l_n_m)
{
	char **args = token->args;

	return(absolute_or_relative_path(args, token, l_n_m));
}