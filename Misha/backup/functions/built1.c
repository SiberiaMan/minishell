#include "builtins.h"

int ft_pwd()
{
	char *pwd;
	char *buff;
	int len;

	buff = NULL;
	pwd = getcwd(buff, 0);
	len = ft_strlen(pwd);
	write(1, pwd, len);
	write(1, "\n", 1);
	free(buff);
	return (0);
}

int ft_echo(char **str)
{
	int len;
	int opt;
	//option доставать из args
	opt = 0;
	while(*str)
	{
		if(!ft_strcmp(*str, "-n"))
			flag = 1;
		else
		len = ft_strlen(str);
		if (option == 0)
		{
			write(1, str, len);
			write(1, "\n", 1);
		} else
			write(1, str, len);
		str++;
	}
	return (0);
}
int ft_cd(char *path)
{
	int res;

	res = chdir(path);
	return (res);
}
