/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:04:52 by daeha             #+#    #+#             */
/*   Updated: 2024/04/28 19:15:36 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_proc(int *r_fd, int *w_fd, int n, int brother)
{
	char buf[100];
	char **argv;
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

	read(read_fd, buf, 100);
	write(write_fd, buf, strlen(buf));
	printf("%d-th child\n%s\n",n, buf);

	close(r_fd[1]);
	close(w_fd[0]);
	close(read_fd);
	close(write_fd);
	exit(0);
}

int main(int argc, char **a, char **envp)
{
	char *argv[] = {"echo", "$(test)", NULL};

	unlink("output.txt");

	int in = open("input.txt", O_RDWR);
	int	out = open("output.txt", O_RDWR | O_CREAT, 777);
	
	int i = 0;

	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	if (execve("/bin/echo", argv, envp) == -1)
		printf("120931238901203803289032890329083");
	return (0);
}
void	child_proc(int *r_fd, int *w_fd, int n, int brother)
{
	char buf[100];
	char **argv;
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

	read(read_fd, buf, 100);
	write(write_fd, buf, strlen(buf));
	printf("%d-th child\n%s\n",n, buf);

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
