#include "history.h"

void sig_slash(int signum)
{
	(void)(signum);
}

void sig_c(int signum)
{
	(void)(signum);
	write(1, "\n", 1);
	tputs("minishell=):", 1, ft_putint);
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

int main(int argc, char const **argv)
{
	(void)(argv);
	(void)(argc);
	t_gnl *gnl;
	//struct termios *term;
	//struct termios *reset_term;
	//char *term_name;

	gnl = gnl_init();
	if (!gnl)
		free_gnl(gnl);
	signal(SIGQUIT, sig_slash); // ctrl + slash
	signal(SIGINT, sig_c); //ctrl + C
	tcgetattr(0, gnl->term); //получить атрибут терминала
	tcgetattr(0, gnl->reset_term);
	set_terminal(gnl->term_name, gnl->term, gnl->reset_term, 1);
	input(gnl);
	return(0);
}







