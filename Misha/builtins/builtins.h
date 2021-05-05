#ifndef BUILTINS_H
# define BUILTINS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../tokenizer/tokenizer.h"

int	choose_builtin(t_line_n_mask *l_n_m, t_token *token, size_t i);
void	free_vars(char **vars, int i);
int		count_vars(char **vars);
char	**copy_envp(char **envp);
char	**export_one_var(char *var, char **envp, t_line_n_mask *l_n_m,
					  t_token *token);
char	**check_for_equal_sign(char **vars);
int count_valid_vars(char **vars);
char	**collect_valid_vars(int count, char **vars, t_line_n_mask *l_n_m,
						  t_token *token);
char	**manage_duplication(char **p_vars, char **p_envp, t_line_n_mask
			*l_n_m, t_token *token);
int	ft_echo(char **str, char **envp);
///char	**unset(char **vars, char **envp);
///void ft_pwd();
///void ft_echo(char *str, int option);
///int ft_cd(char *path);
void	sort_vars(char **v);
void	free_export(t_line_n_mask *l_n_m, t_token *token, char **vars, int i);
//int		choose_builtin(t_line_n_mask *l_n_m, t_token *token);
int		ft_export(t_line_n_mask *l_n_m, t_token *token);
//int		ft_unset(t_line_n_mask *l_n_m, t_token *token);
//int		ft_env(t_line_n_mask *l_n_m, t_token *token);
//void	free_export(t_line_n_mask *l_n_m, t_token *token, char **vars, int i);
//int		choose_builtin(t_line_n_mask *l_n_m, t_token *token);

#endif