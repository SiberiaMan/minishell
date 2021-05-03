#include "minishell.h"

void foo()
{
	int fdout = open("/home/phili/Desktop/project/Misha/file.txt",
				   O_RDWR | O_TRUNC);
	dup2(fdout, 1);
	close(fdout);
}

void bar()
{
	int fdin = open("/home/phili/Desktop/project/Misha/file1.txt",
					 O_RDWR);
	dup2(fdin, 0);
	close(fdin);
}

int main(/*char *line*/)
{
	int processes[3];
	int **pipes = (int**)malloc(sizeof(int*) * 2);
	for (int i = 0; i < 2; i++)
	{
		pipes[i] = (int*)malloc(sizeof(int) * 2);
		pipe(pipes[i]);
	}
	int ret = fork();
	if (ret == 0) {
		//bar();
		//foo();
		close(pipes[0][0]); //// cat -e > file.txt | cat -e
		close(pipes[0][1]);
		close(pipes[1][0]);
		dup2(pipes[1][1], 1);
		char *args[3] = {"/usr/bin/ls", "-la", 0};
		execve(args[0], args, 0);
		//printf("child exit\n");
		perror("Error");
		exit(127);
	}
	processes[0] = ret;
	int pret = fork();
	if (pret == 0) {
		close(pipes[0][0]); //// cat -e > file.txt | cat -e
		close(pipes[0][1]);
		close(pipes[1][1]);
		dup2(pipes[1][0], 0);
		printf("child here2\n");
		char *args[3] = {"/usr/bin/cat", "-e", 0};
		execve(args[0], args, 0);
		printf("child exit\n");
		perror("Error");
		exit(127);
	}
	processes[1] = pret;
	for (int i = 0; i < 2; i++)
	{
		close (pipes[i][0]);
		close (pipes[i][1]);
	}
	int status;
	int i = 0;
	while (i < 2 && waitpid(processes[i], &status, 0))
		i++;
	status = 1;
}

