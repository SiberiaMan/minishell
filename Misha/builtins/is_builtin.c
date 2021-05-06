#include "builtins.h"
#include "../executing/executing.h"

void choose_builtin(t_line_n_mask *l_n_m, t_token *token, size_t i)
{
	int fdin;
	int fdout;

	fdin = dup(0);
	if (fdin < 0)
		return (dup_error(l_n_m));
	fdout = dup(1);
	if (fdout < 0)
		return (dup_error(l_n_m));
	change_io(l_n_m, token, i, 0);
	/// **args -> token->args
	/// status ->l_n_m->status везде с собой таскать, чтобы делать free, но
	/// записывать только тут 0 или 1
	if (!(ft_strcmp(token->lower, "echo")))
		l_n_m->status = ft_echo(token->args);
	else if	(!(ft_strcmp(token->lower, "cd")))
		l_n_m->status = ft_cd(token, l_n_m);
	else if (!(ft_strcmp(token->lower, "pwd")))
		l_n_m->status = ft_pwd();
	else if (!(ft_strcmp(token->lower, "env")))
		l_n_m->status=ft_env(*l_n_m->env);
	else if (!(ft_strcmp(token->lower, "export")))
		l_n_m->status = ft_export(l_n_m, token);
	else if (!(ft_strcmp(token->lower, "unset")))
		l_n_m->status = ft_unset(l_n_m, token);
	if (dup2(fdin, 0) < 0)
		return (dup_error(l_n_m));
	if (dup2(fdout, 1) < 0)
		return (dup_error(l_n_m));
}