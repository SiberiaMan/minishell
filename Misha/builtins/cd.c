#include "builtins.h"

int cd_error(char **args)
{
	int count;
	int i;

	i = 1;
	count = count_vars(args);
	ft_putstr_fd("minishell: cd: ", 2);
	while(args[i])
	{
		ft_putstr_fd(args[i], 2);
		if(i < count - 1)
			ft_putchar_fd('/', 2);
		i++;
	}
	ft_putstr_fd(": No such file or directory\n", 2);
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

int join_oldpwd(t_token *token, t_line_n_mask *l_n_m)
{
	char **new_envp;
	char *pwd;
	char *oldpwd;

	pwd = return_new_pwd();
	pwd = ft_strjoin("PWD=", pwd);
	oldpwd = ft_strdup("OLDPWD=");
	oldpwd = ft_strjoin(oldpwd, return_env("PWD", *l_n_m->env));
	char **ex;
	ex = (char **)malloc((sizeof(char *) * 4));
	ex[0] = ft_strdup("export");
	ex[1] = ft_strdup(pwd);
	ex[2] = ft_strdup(oldpwd);
	ex[3] = NULL;
	new_envp = manage_duplication(ex, *l_n_m->env, l_n_m, token);
	*l_n_m->env = new_envp;
	return(0);
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
	///if(!path)
	///free
	i = 1;
	if (args[1] == NULL)
		res = change_to_home_dir(*l_n_m->env);
	else
	{
		while (args[i])
		{
			ptr = path;
			path = ft_strjoin(path, args[i]);
			///if(!path)
			///free
			free(ptr);
			i++;
		}
		res = change_directory(path);
	}
//	printf("res = %d\n", res);
	if (res == 0)
		return(join_oldpwd(token, l_n_m));
	else
		return(cd_error(args));
}

int ft_cd(t_token *token, t_line_n_mask *l_n_m)
{
	char **args = token->args;

	return(absolute_or_relative_path(args, token, l_n_m));
}