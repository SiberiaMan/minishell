#ifndef HISTORY_H
# define HISTORY_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <term.h>
#include <string.h>
#include <curses.h>
#include <termcap.h> 

typedef struct s_list
{
    struct s_list *next;
    struct s_list *prev;
    char *line;
} t_list;

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int	lst_create_add(t_list **lst, char *line);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strchr(char *s);
char	*ft_strdup(const char *s1);
int ft_putint(int c);
void ft_putstr(char *str);
void list_swap(t_list *a, t_list *b);

#endif