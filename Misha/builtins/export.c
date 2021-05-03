#include "builtins.h"

void	free_export(t_line_n_mask *l_n_m, t_token *token, char **vars, int i)
{
	if(vars)
		free_vars(vars, i);
	free_token_n_structure_exit(token, l_n_m);
}

char	**export_one_var(char *var, char **envp, t_line_n_mask *l_n_m, t_token *token)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc((sizeof(char *) * (count_vars(envp) + 2)));
	if (!res)
		free_export(l_n_m, token, NULL, 0);
	while (*envp)
	{
		res[i] = ft_strdup(*envp);
		if (!res[i])
			free_export(l_n_m, token, res, i - 1);
		envp++;
		i++;
	}
	res[i] = ft_strdup(var);
	if (!res[i])
		free_export(l_n_m, token, res, i - 1);
	res[i+1] = NULL;
	free(var);
	return (res);
}

int ft_export(t_line_n_mask *l_n_m, t_token *token)
{
	// **args -> token->args
	// status ->l_n_m->status
	char **valid_vars;
	int count;
	char **new_env;

	if (!token->args[1])
	{
		sort_vars(*l_n_m->env);
		return (0);
	}
	count = count_valid_vars(token->args);
	if (count > 0)
		valid_vars = collect_valid_vars(count, token->args, l_n_m, token);
	else
		return (1);
	new_env = manage_duplication(valid_vars, *l_n_m->env, l_n_m, token);
	*l_n_m->env = new_env;
	return (0);
}

// -1 (malloc) // -> exit + free
// 0 хорошо
// 1 syntax error // l_n_m->status <- 1
// l_n_m->env (env - char **) export(char ***env)

//int main(int argc, char **argv, char **envp)
//{
//	char **copy;
//	char **export_;
//	char **unset_;
//	char *massiv[] = {"USER=0", "TERM=lol", "TERM=haha",  "kek=2", "lol=3",
//					  "kek=4", NULL};
//	char *massiv_2[] = {"kek", "lol", NULL};
//
//	copy = copy_envp(envp); ///не может быть ликов
//	export_ = export(massiv, copy);
//	if(!export_)
//		return(-1);
//	copy = export_;
//	while(*export_)
//	{
//		printf("%s\n", *export_);
//		export_++;
//	}
//	unset_ = unset(massiv_2, copy);
//	printf("\n\n\n");
//	if(unset_)
//	{
//		while (*unset_)
//		{
//			printf("%s\n", *unset_);
//			unset_++;
//		}
//	}
//	sleep(100);
//	return(0);
//}