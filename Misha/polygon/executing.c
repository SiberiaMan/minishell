#include "../minishell.h"

int main(/*char *line*/)
{
	int processes[2];
	int fd[2];
	pipe(fd);
	int ret = fork();
	if (ret == 0) {
		/*dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]); */
		printf("child here1\n");
		int fd1 = open("/home/phili/Desktop/project/Misha/a.o1ut", O_RDWR);
		if (fd1 < 0)
		{
			printf("No such file or directory\n");
			exit(1);
		}
		char *args[2] = {"/home/phili/Desktop/project/Misha/a.out", 0};
		if (execve(args[0], args, 0) < 0)
			printf("child exit\n");
		//perror("Error");
		exit(1);
	}
	processes[0] = ret;
	/*int pret = fork();
	if (pret == 0) {
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		printf("child here2\n");
		char *args[3] = {"/usr/bin/cat", "-e", 0};
		execve(args[0], args, 0);
		printf("child exit\n");
		perror("Error");
		exit(127);
	}
	processes[1] = pret;
	close(fd[0]);
	close(fd[1]); */
	int status = 0;
	int i = 0;
	while (i < 1 && waitpid(processes[i], &status, 0))
	{
		printf("%d\n", status);
		i++;
	}

}

