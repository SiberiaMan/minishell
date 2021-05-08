#include "builtins.h"
#include "errno.h"
#include "string.h"

int	ft_pwd(void)
{
	char	*pwd;
	char	*buff;
	size_t	len;

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

char	*return_new_pwd(void)
{
	char	*pwd;
	char	*buff;

	buff = NULL;
	pwd = getcwd(buff, 0);
	free(buff);
	return (pwd);
}

int	cd_error(char *path, int res)
{
	char	*message;

	message = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	change_directory(char *path)
{
	int	res;

	res = chdir(path);
	free(path);
	return (res);
}
