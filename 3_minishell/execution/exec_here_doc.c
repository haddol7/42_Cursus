/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:50:09 by daeha             #+#    #+#             */
/*   Updated: 2024/06/06 18:45:28 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "execution.h"

static void	proc_here_doc(char **cmd);
static void	heredoc(char *delim, char *filename);
static char	*name_tmp_file(void);

void	exec_here_doc(t_node *node)
{
	
	if (node == NULL || node->type == N_CMD)
		return ;
	printf("exec -> %s\n", node->right->cmd[0]);
	if (node->type == N_HERE_DOC)
		proc_here_doc(node->right->cmd);
	exec_here_doc(node->left);
	exec_here_doc(node->right);
}

static void	proc_here_doc(char **cmd)
{
	int		pid;
	char	*filename;

	filename = name_tmp_file();
	pid = fork();
	if (!pid)
		heredoc(cmd[0], filename);
	else
	{
		waitpid(pid, 0, 0);
		free(cmd[0]);
		cmd[0] = filename;
	}
}

static char	*name_tmp_file(void)
{
	char	*name;
	char	*num;
	char	*tmp;
	int		n;
	
	n = 1;
	name = ft_strdup("/tmp/heredoc_0");
	while (!access(name, F_OK))
	{
		num = ft_itoa(n++);
		tmp = ft_strjoin("/tmp/heredoc_", num);
		free(num);
		free(name);
		name = tmp;
	}
	return (name);
}

static void	heredoc(char *delim, char *filename)
{
	char	*str;
	int		len_d;
	int		len_s;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		redir_error(delim);
	len_d = ft_strlen(delim);
	while (TRUE)
	{	
		str = readline("> ");
		if (str)
			len_s = ft_strlen(str);
		if (!str || (len_s == len_d && !ft_strncmp(str, delim, len_d)))
			break ;
		write(fd, str, len_s);
		free(str);
	}
	if (str != NULL)
		free(str);
	close(fd);
	exit(EXIT_SUCCESS);
}
