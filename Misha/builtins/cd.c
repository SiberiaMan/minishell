#include "builtins.h"

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

int change_to_prev_dir(char **envp,  t_token *token, t_line_n_mask *l_n_m)
{
	char *ptr;
	char *pwd;
	char *last_slash;
	int len;
	char *path;

	///когда запоминать OLDPWD
	(void)(token);
	(void)(l_n_m);
	len = 1;
	pwd = return_pwd(envp);
	if (pwd)
	{
		ptr = pwd;
		last_slash = ft_strrchr(pwd, '/');
		while (ptr != last_slash && ptr != '\0')
		{
			ptr++;
			len++;
		}
		path = ft_calloc(len, 1);
		///if(!path)
		///free
		ft_memcpy(path, pwd, len - 1);
	}
	return (change_directory(path));
}


int absolute_or_relative_path(char **args, t_token *token, t_line_n_mask *l_n_m)
{
	int i;
	char *ptr;
	char *path;

	(void)(token);
	(void)(l_n_m);
	path = ft_calloc(1, 1);
	///if(!path)
	///free
	i = 1;
	while(args[i])
	{
		ptr = path;
		path = ft_strjoin(path, args[i]);
		///if(!path)
		///free
		free(ptr);
		i++;
	}
	//printf("path = %s\n", path);
	return (change_directory(path));
}

int ft_cd(t_token *token, t_line_n_mask *l_n_m)
{
	char **args = token->args;
	char **envp = *l_n_m->env;


	if (!args[1])
		return(change_to_home_dir(envp));
	else if (!ft_strcmp(args[1], ".."))
		return(change_to_prev_dir(envp, token, l_n_m));
	else
		return(absolute_or_relative_path(args, token, l_n_m));
}