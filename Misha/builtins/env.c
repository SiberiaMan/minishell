#include "builtins.h"

int ft_env(char **envp)
{
	char **ptr;

	ptr = envp;
	while(*ptr)
	{
		ft_putstr_fd(*ptr, 1);
		ft_putchar_fd('\n', 1);
		ptr++;
	}
	return (0);
}