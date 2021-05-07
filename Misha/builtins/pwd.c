#include "builtins.h"

int ft_pwd()
{
	char *pwd;
	char *buff;
	size_t len;

	buff = NULL;
	pwd = getcwd(buff, 0);
	if (pwd)
	{
		len = ft_strlen(pwd);
		write(1, pwd, len);
		write(1, "\n", 1);
		free(buff);
		free(pwd);
		return (0);
	}
	return (1);
}

char *return_new_pwd()
{
	char *pwd;
	char *buff;

	buff = NULL;
	pwd = getcwd(buff, 0);
	free(buff);
	return (pwd);
}