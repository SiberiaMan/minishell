#include "minishell.h"

void foo(int fd1)
{
	dup2(fd1, 1);
	close(fd1);
}

int main(/*char *line*/)
{
	int processes[3];
	int fd[2];
	pipe(fd);
	int ret = fork();
	if (ret == 0) {
		dup2(fd[1], 1);
		int fd1 = open("/Users/dchani/Desktop/minishell_project/Misha/file.txt",
				O_RDWR | O_TRUNC);
		foo(fd1);
		//dup2(fd1, 1);
		//close(fd1);
		close(fd[1]); //// cat -e > file.txt | cat -e
		close(fd[0]);
		char *args[2] = {"/bin/cat", 0};
		execve(args[0], args, 0);
		printf("child exit\n");
		perror("Error");
		exit(127);
	}
	processes[0] = ret;
	int pret = fork();
	if (pret == 0) {
		int fd1 = open("/Users/dchani/Desktop/minishell_project/Misha/file1"
				 ".txt",
					   O_RDWR);
		dup2(fd[0], 0);
		dup2(fd1, 0);
		close(fd1);
		close(fd[0]);
		close(fd[1]);
		printf("child here2\n");
		char *args[3] = {"/bin/cat", "-e", 0};
		execve(args[0], args, 0);
		printf("child exit\n");
		perror("Error");
		exit(127);
	}
	processes[1] = pret;
	close(fd[0]);
	close(fd[1]);
	int status;
	int i = 0;
	while (i < 2 && waitpid(processes[i], &status, 0))
		i++;
	status = 1;
}

