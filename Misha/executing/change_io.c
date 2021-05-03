#include "executing.h"

void change_io(t_line_n_mask *l_n_m, t_token token, size_t i, int fdout, int
fdin)
{
	int temp_fdin;
	int temp_fdout;
	int tmpin;
	int tmpout;
	int k;

	k = 0;
	while (k < l_n_m->cnt_pipes + 1)
	{
		if (i != k)
			close(l_n_m->pipes[k][0]);
		if (i + 1 != k)
			close(l_n_m->pipes[k][1]);
		k++;
	}
	temp_fdin = dup(fdin); // 0
	temp_fdout = dup(fdout); // 1
	if (i == 0)
	{
		tmpin = dup(temp_fdin); /// handle dup
		tmpin = dup(token.fd_from);
		dup2(tmpin, 0);
		close(tmpin);
		if (i != l_n_m->cnt_pipes)
		{
			tmpout = dup(l_n_m->pipes[i + 1][1]); ///handle dup
			if (token.fd_to != 1)
				tmpout = token.fd_to;
			dup2(tmpout, 1); /// handle dup
			close(tmpout);
		}
	}
	if (i == l_n_m->cnt_pipes)
	{
		if (i != 0)
		{
			tmpin = dup(l_n_m->pipes[i][0]); /// handle dup
			if (token.fd_from != 0)
				tmpin = token.fd_from;
			dup2(tmpin, 0);
			close(tmpin);
		}
		tmpout = dup(temp_fdout); /// handle dup
		tmpout = dup(token.fd_to);
		dup2(tmpout, 1); /// handle dup
		close(tmpout);
	}
	if (i != 0 && i != l_n_m->cnt_pipes)
	{
		tmpin = dup(l_n_m->pipes[i][0]); /// handle dup
		tmpout = dup(l_n_m->pipes[i + 1][1]); /// handle dup
		if (token.fd_to != 1)
			tmpout = token.fd_to;
		if (token.fd_from)
			tmpin = token.fd_from;
		dup2(tmpin, 0); /// handle dup
		dup2(tmpout, 1); /// handle dup
		close(tmpin);
		close(tmpout);
	}
}