#include "builtins.h"
#include "../executing/executing.h"
//тебе надо сделать функцию, которая на вход будет принимать указатели на мои структуры (пусть это будет функция 1)
//эта функция сработает если первый элемент массива явялется билтином (я проверяю)
//в этой функции ты определяешь какой именно билтин нужно использовать. в моей структуре есть касающиеся тебя status и env, соответсвенно,
// работая с ними ты передаешь в функции (билтины) их по указателю, в случае status это *status, в случае **env это ***env.
//если какой-либо из билтинов сработал плохо (ошибка не касающася маллока), то статус устанавливаешь 1, чистишь все(если что-то выделяла) и выходишь ,
// если ошибка маллока, то возвращаешься из функции билтина в функцию 1, чистишь все мои структуры и exit


//хотя вот это
//"""в этой функции ты определяешь какой именно билтин нужно использовать. в моей структуре есть касающиеся тебя status и env, соответсвенно,
// работая с ними ты передаешь в функции (билтины) их по указателю, в случае status это *status, в случае **env это ***env""""
//можешь делать на свое усмотрение
//короче задача какая, тебе надо сделать функцию которая изменяет мою структуру (это env и статус) а в случае ошибки маллока например, чистит структуры и делает exit
//в этой функции ты определяешь какой именно билтин нужен, но не определяешь является ли билтином первый аргумент, тк я деаю это за тебя
// void func(t_line_n_mask *l_n_m, t_token *token)
// **args -> token->args
// status ->l_n_m->status
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
	//else if	(!(ft_strcmp(token->args[0], "cd"))
	//	l_n_m->status = ft_cd(t_line_n_mask *l_n_m, t_token *token);
	//else if (!(ft_strcmp(token->args[0], "pwd"))
	//	l_n_m->status = ft_pwd(t_line_n_mask *l_n_m, t_token *token);
	//else if (!(ft_strcmp(token->args[0], "env"))
	//	l_n_m->status = ft_env(t_line_n_mask *l_n_m, t_token *token);
	if (!(ft_strcmp(token->lower, "export")))
		l_n_m->status = ft_export(l_n_m, token);
	//else if (!(ft_strcmp(token->args[0], "unset"))
	//	l_n_m->status = ft_unset(t_line_n_mask *l_n_m, t_token *token);
	if (dup2(fdin, 0) < 0)
		return (dup_error(l_n_m));
	if (dup2(fdout, 1) < 0)
		return (dup_error(l_n_m));
}