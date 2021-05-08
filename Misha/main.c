#include "minishell.h"
#include "builtins/builtins.h"

void	parse_n_execute(t_gnl *gnl, char ***env)
{
	size_t	i;
	char 	*mask;


	i = 0;
	mask = ft_calloc(ft_strlen(gnl->history->line) + 1, sizeof(char));
	if (!mask)
	{
		free_gnl(gnl);
		exit (1);
	}
	while (i < ft_strlen(gnl->history->line))
		mask[i++] = '1';
	if (!get_mask_normal(gnl->history->line, mask))
		return ;
	if (!parser(gnl->history->line, mask))
	{
		free(mask); /// по парсингу не прошла строка, возращаемся в терминал
		gnl->status = 258;
		return ;
	}
	handle_semicolons(gnl, mask, env);
	free(mask); ///  прошел парсинг и команды успешно выполнились
}

int comparison(t_gnl *gnl)
{
	if(!ft_strcmp(gnl->str, "\e[D"))
		ft_memset(gnl->str, 0, 10);
	if(!ft_strcmp(gnl->str, "\e[C"))
		ft_memset(gnl->str, 0, 10);
	if(!ft_strcmp(gnl->str, "\t"))
		ft_memset(gnl->str, 0, 10);
	if(!ft_strcmp(gnl->str, "\n"))
		return(enter(gnl));
	if (!ft_strcmp(gnl->str, "\e[A"))
		up(gnl);
	else if (!ft_strcmp(gnl->str, "\e[B"))
		down(gnl);
	else if (ft_strcmp(gnl->str, "\n") && ft_strcmp(gnl->str, "\4"))
		get_command(gnl);
	if (!ft_strcmp(gnl->str, "\177"))
		backspace(gnl);
	if(!ft_strcmp(gnl->str, "\4"))
	{
		ft_memset(gnl->str, 0, 10);
		if (ft_strlen(gnl->edit) == 0)
		{
			free_gnl(gnl);
			ft_putstr_fd("\nexit\n", 1);
			set_terminal(gnl->term_name, gnl->term, gnl->reset_term, 0);
			exit(0);
		}
	}
	return(0);
}

int input(t_gnl *gnl)
{
	tputs("minishell=):", 1, ft_putint);
	tputs(save_cursor, 1, ft_putint);
	while (1)
	{
		signal(SIGINT, sig_c);
		set_terminal(gnl->term_name, gnl->term, gnl->reset_term, 1);
		ft_memset(gnl->str, 0, 10);
		gnl->l = read(0, gnl->str, 10);
		if (comparison(gnl) == 1)
		{
			signal(SIGINT, sig_c_2);
			set_terminal(gnl->term_name, gnl->term, gnl->reset_term, 0);
			if (g_var == 1 && gnl->status != 130)
			{
				gnl->status = g_var;
				g_var = 0;
			}
			else if (g_var == 1 && gnl->status)
				g_var = 0;
			parse_n_execute(gnl, gnl->env);
			set_terminal(gnl->term_name, gnl->term, gnl->reset_term, 1);
			tputs("minishell=):", 1, ft_putint);
			tputs(save_cursor, 1, ft_putint);
		}
	}
	return(0);
}

void set_terminal(char *term_name, struct termios *term, struct termios
		*reset_term, int flag)
{
	if (flag == 1)
	{
		term->c_lflag &= ~(ECHO);
		term->c_lflag &= ~(ICANON);
		term->c_cc[VTIME] = 0;
		term->c_cc[VMIN] = 1;
		tcsetattr(0, TCSANOW, term);
		tgetent(0, term_name); //проверять на возвращаемые значения!
	}
	if (flag == 0)
		tcsetattr(0, TCSANOW, reset_term);
}

int main(int argc, char const **argv, char **env)
{
	(void)(argv);
	(void)(argc);
	t_gnl *gnl;

	if (!env[0])
		return(0);
	char **envp = copy_envp(env); /// handle
	if (!envp)
		exit (1);
	size_t i = 0;
	//struct termios *term;
	//struct termios *reset_term;
	//char *term_name;

	gnl = gnl_init();
	if (!gnl)
		free_gnl(gnl);
	gnl->env = &envp;
	signal(SIGQUIT, sig_slash); // ctrl + slash
	signal(SIGINT, sig_c); //ctrl + C
	tcgetattr(0, gnl->term); //получить атрибут терминала
	tcgetattr(0, gnl->reset_term);
	set_terminal(gnl->term_name, gnl->term, gnl->reset_term, 1);
	input(gnl);
	return(0);
}







