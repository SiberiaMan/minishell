#include "minishell.h"

int main(/*char *line*/)
{
	int processes[3];
	int tmpin = dup(0);
	int tmpout = dup(1);
	int fdin = dup(tmpin);
	int
	int fdout;
	int ret = fork();
	if (ret == 0) {
		//int fd3 = open("/Desktop/project/Misha/exec/a.out", O_RDONLY);
		//dup2(fd3, 0);
		//close(fd3);
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		printf("child here1\n");
		char *args[2] = {"/usr/bin/cat", 0};
		execve(args[0], args, 0);
		printf("child exit\n");
		perror("Error");
		exit(127);
	}
	//int fd1[2]; // new pipe
	dup2(fd[0], 0);
	pipe(fd);
	processes[0] = ret;
	int pret = fork();
	if (pret == 0) {
		//int fd4 = open("/home/phili/Desktop/project/Misha/main.c", O_RDONLY);
		//dup2(fd4, 0);
		//close(fd[0]);
		//close(fd[1]);
		//dup2(fd[0], 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		//close(fd1[1]);
		//close(fd1[0]);
		printf("child here2\n");
		char *args[3] = {"/usr/bin/grp", "kek", 0};
		execve(args[0], args, 0);
		printf("child exit\n");
		perror("Error");
		exit(127);
	}
	processes[1] = pret;
	//printf("parent here\n");
	//wait(0);
	int kek = fork();
	if (kek == 0) {
		//int fd1 = open("/Users/dchani/Desktop/shell/main.c", O_RDONLY);
		//dup2(fd1, 0); // priority redirect vs pipe
		dup2(fd1[0], 0);
		close(fd1[0]);
		close(fd[0]);
		close(fd1[1]);
		close(fd[1]);
		char *args[3] = {"/bin/ls", "-la", 0};
		execve(args[0], args, 0);
		perror("Error");
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	close(fd1[0]);
	close(fd1[1]);
	processes[2] = kek;
	//close(fd[0]);
	//close(fd[1]); */
	int status;
	int i = 0;
	while (i < 3 && waitpid(processes[i], &status, 0))
		i++;
	status = 1;
	/*while (status)
	{
		scanf("%d", &status);
	} */
	//printf("%d\n", status);
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

