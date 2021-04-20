#include "minishell.h"

int main(/*char *line*/)
{
	int processes[3];
	int fd[2];
	pipe(fd);
	int ret = fork();
	if (ret == 0) {
		//int fd1 = open("/dev/random", O_RDONLY);
		//dup2(fd1, 0);
		//close(fd1);
		dup2(fd[1], 1);
		close(fd[1]);
		//close(fd[0]);
		printf("child here\n");
		char *args[3] = {"/bin/cat", "-e", 0};
		execve(args[0], args, 0);
		printf("child exit\n");
		perror("Error");
		exit(0);
	}
	processes[0] = ret;
	int pret = fork();
	if (pret == 0) {
		//int fd1 = open("/dev/random", O_RDONLY);
		//dup2(fd1, 0);
		//close(fd1);
		dup2(fd[1], 1);
		close(fd[1]);
		//close(fd[0]);
		printf("child here\n");
		char *args[3] = {"/bin/cat", "-e", 0};
		execve(args[0], args, 0);
		printf("child exit\n");
		perror("Error");
		exit(0);
	}
	processes[1] = pret;
	//printf("parent here\n");
	//wait(0);
	int kek = fork();
	if (kek == 0) {
		int fd1 = open("/Users/dchani/Desktop/shell/main.c", O_RDONLY);
		//dup2(fd1, 0); // priority redirect vs pipe
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		char *args[4] = {"/bin/ls", "-la", 0};
		execve(args[0], args, 0);
		perror("Error");
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	processes[2] = kek;
	int status;
	int i = 0;
	while (i < 3 && waitpid(processes[i], &status, 0))
		i++;
	//printf("kek\n");
	// dup2(fd[1], 1);
	// close(fd[1]);
	// write(1, "kek\n", strlen("kek\n"));
	//printf("lol\n");
	// char buf[4];
	// read(fd[0],buf, 4);
	// write(tmpout, buf, strlen(buf));
	// char buf2[8];
	// read(fd[0], buf2, 8);
}

