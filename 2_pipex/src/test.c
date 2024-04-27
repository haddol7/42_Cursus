#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void	child_proc(int *r_fd, int *w_fd, int n, int brother)
{
	char buf[100];
	int	read_fd;
	int	write_fd;

	//open fd
	if (n == 0)
	{
		read_fd = open("input.txt", O_RDONLY);
		close(r_fd[0]);
	}
	else
		read_fd = r_fd[0];
	if (n == brother - 1)
	{
		write_fd = open("output.txt", O_WRONLY | O_CREAT, 777);
		close(w_fd[1]);
	}
	else
		write_fd = w_fd[1];
	
	//read & write
	if (read(read_fd, buf, 100) == -1)
	{
		printf("errno - %d\n", errno);
		perror(NULL);
		exit(1);
	}
	write(write_fd, buf, strlen(buf));
	printf("%d-th child\n%s\n",n, buf);

	//close fd
	close(r_fd[1]);
	close(w_fd[0]);
	close(read_fd);
	close(write_fd);
	exit(0);
}

int	main(int argc, char *argv[])
{
	int fd[2];
	int fd2[2];
	int	pid;
	int	n;

	n = 3;
	unlink("output.txt");
	pipe(fd);
	pipe(fd2);
	for (int i = 0; i < n; i++)
	{
		if (i != 0)
		{
			if (i % 2 == 1)
			{
				close(fd[1]);
				close(fd[0]);
				pipe(fd);
			}
			else
			{
				close(fd2[1]);
				close(fd2[0]);
				pipe(fd2);
			}
		}
		pid = fork();
		if (pid == 0 && i % 2 == 0)
			child_proc(fd, fd2, i, n);
		else if (pid == 0 && i % 2 == 1)
			child_proc(fd2, fd, i, n);
	}
	for(int i = 0; i < n; i++)
		wait(NULL);
	close(fd[1]);
	close(fd[0]);
	close(fd2[1]);
	close(fd2[0]);
	printf("parent dead\n");
} 
