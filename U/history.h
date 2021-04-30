#ifndef HISTORY_H
# define HISTORY_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <term.h>
#include <curses.h>
#include <termcap.h>

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
};

char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
int		lst_create_add(t_list **lst, char *line);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_putint(int c);
void	ft_putstr(char *str);
int		ctrl_d(t_gnl *gnl);
int		up(t_gnl *gnl);
int		down(t_gnl *gnl);
int		enter(t_gnl *gnl);
int		backspace(t_gnl *gnl);
int		input(t_gnl *gnl);
int		get_command(t_gnl *gnl);
char	*ft_strchr(const char *s, int c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
void 	set_terminal(char *term_name, struct termios *term, struct termios
			*reset_term,  int flag);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
t_gnl *gnl_init(void);
int check_for_exit(char *line, t_gnl *gnl);
void free_gnl(t_gnl *gnl);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memset(void *b, int c, size_t len);

#endif