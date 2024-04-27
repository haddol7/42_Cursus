#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void	child_proc(int *r_fd, int *w_fd, int n)
{
	char buf[100];
	int	read_fd;
	int	write_fd;

	if (n == 0)
	{
		read_fd = open("input.txt", O_RDONLY);
		close(r_fd[0]);
	}
	else
		read_fd = r_fd[0];
	if (n == 2)
		write_fd = open("output.txt", O_WRONLY | O_CREAT, 777);
	else
		write_fd = w_fd[1];
	
	if (read(read_fd, buf, 100) == -1)
	{
		printf("errno - %d\n", errno);
		perror(NULL);
		exit(1);
	}
	write(write_fd, buf, strlen(buf));
	printf("%d-th child\n%s\n",n, buf);

	if (!r_fd)
		close(r_fd[1]);
	if (!w_fd)
		close(w_fd[0]);
	close(read_fd);
	close(write_fd);
}

int	main(int argc, char *argv[])
{
	int fd[2];
	int fd2[2];

	unlink("outfile");
	pipe(fd);
	pipe(fd2);
	int pid = fork();
	if (pid == 0)
		child_proc(fd, fd2, 0);
	else
	{	
		pipe(fd);
		pid = fork();
		if (pid == 0)
			child_proc(fd2, fd, 1);
		else
		{	
			pid = fork();
			if (pid == 0)
				child_proc(fd, NULL, 2);
			else
			{
				wait(NULL);
				wait(NULL);
				wait(NULL);
				close(fd[1]);
				close(fd[0]);
				close(fd2[1]);
				close(fd2[0]);
				printf("parent dead\n");
			}
		}
	}
	
} 
