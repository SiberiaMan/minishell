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

char *return_pwd(char **envp)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(envp[i])
	{
		if(!ft_strncmp(envp[i], "PWD", 3))
		{
			while (envp[i][j] != '=' && envp[i][j] != '\0')
				j++;
			return(&envp[i][j + 1]);
		}
		i++;
	}
	return(NULL);
}

int join_oldpwd(t_token *token, t_line_n_mask *l_n_m)
{
	char *tmp;
	char *oldpwd;
	char *ret_pwd;
	char **new_envp;
	char *pwd;

	oldpwd = ft_strdup("OLDPWD=");
	///if(!oldpwd)
		///
	ret_pwd = return_pwd(*l_n_m->env);
	tmp = oldpwd;
	oldpwd = ft_strjoin(oldpwd, ret_pwd);
	///if(!oldpwd)
	new_envp = export_one_var(oldpwd, *l_n_m->env, l_n_m, token);
	pwd = ft_strdup("PWD=");
	///if (!pwd)
	pwd = ft_strjoin(pwd, return_new_pwd());
	char *unset_pwd[] = {"PWD", NULL};
	new_envp= unset(unset_pwd, new_envp);
	new_envp = export_one_var(pwd, new_envp, l_n_m, token);
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
	if (args[1])
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
	}
	res = change_directory(path);
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