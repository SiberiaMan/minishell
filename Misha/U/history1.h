#ifndef HISTORY1_H
# define HISTORY1_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <term.h>
#include <curses.h>
#include <termcap.h>
#include "../history.h"

typedef struct s_list       t_list;
typedef struct s_gnl		t_gnl;

struct s_list
{
	struct s_list *next;
	struct s_list *prev;
	char *line;
};

struct s_gnl
{
	char ***env;
	char *edit;
	t_list *history;
	int l;
	char *str;
	char *tmp;
	char *saved;
	int flag;
	char *term_name;
	struct termios *term;
	struct termios *reset_term;
	int		status;
};

int		lst_create_add(t_list **lst, char *line);
void	ft_putstr(char *str);
int		ctrl_d(t_gnl *gnl);
int		up(t_gnl *gnl);
int		down(t_gnl *gnl);
int		enter(t_gnl *gnl);
int		backspace(t_gnl *gnl);
int 	input(t_gnl *gnl);
int		get_command(t_gnl *gnl);
void 	set_terminal(char *term_name, struct termios *term, struct termios
			*reset_term,  int flag);
t_gnl *gnl_init(void);
int check_for_exit(char *line, t_gnl *gnl);
void free_gnl(t_gnl *gnl);
int		ft_strcmp(const char *s1, const char *s2);

#endif