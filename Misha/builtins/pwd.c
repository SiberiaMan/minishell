#include "builtins.h"

int ft_pwd()
{
	char *pwd;
	char *buff;
	size_t len;

	buff = NULL;
	pwd = getcwd(buff, 0);
	len = ft_strlen(pwd);
	write(1, pwd, len);
	write(1, "\n", 1);
	free(buff);
	return (0);
}