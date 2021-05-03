#ifndef BUILTINS_H
# define BUILTINS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void ft_putstr(char *str);
void	free_vars(char **vars, int i);
int		count_vars(char **vars);
char	**copy_envp(char **envp);
int		ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
int		ft_isalpha(int c);
//char		**manage_duplication(char **p_vars, char **p_envp, );
char	**export_one_var(char *var, char **envp);
char	**check_for_equal_sign(char **vars);
int count_valid_vars(char **vars);
char **collect_valid_vars(int count, char **vars);
///char	**unset(char **vars, char **envp);
void	ft_putstr_fd(char *s, int fd);
///void ft_pwd();
///void ft_echo(char *str, int option);
///int ft_cd(char *path);
void	sort_vars(char **v);
//int		choose_builtin(t_line_n_mask *l_n_m, t_token *token);
//int		ft_export(t_line_n_mask *l_n_m, t_token *token);
//int		ft_unset(t_line_n_mask *l_n_m, t_token *token);
//int		ft_env(t_line_n_mask *l_n_m, t_token *token);
//void	free_export(t_line_n_mask *l_n_m, t_token *token, char **vars, int i);
//int		choose_builtin(t_line_n_mask *l_n_m, t_token *token);

#endif