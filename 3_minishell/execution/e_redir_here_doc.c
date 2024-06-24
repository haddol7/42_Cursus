/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redir_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:50:09 by daeha             #+#    #+#             */
/*   Updated: 2024/06/25 00:18:25 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

static void	proc_here_doc(char **cmd);
static void	write_heredoc(char *delim, char *filename);
static char	*name_tmp_file(void);

extern int	g_status;

void	exec_here_doc(t_node *node)
{
	if (g_status == 128 + SIGINT)
		return ;
	if (node == NULL || node->type == N_CMD)
		return ;
	if (node->type == N_HERE_DOC)
		proc_here_doc(node->right->cmd);
	exec_here_doc(node->left);
	exec_here_doc(node->right);
}

static void	proc_here_doc(char **cmd)
{
	pid_t	pid;
	char	*filename;
	int		*status;

	status = get_status();
	filename = name_tmp_file();
	sig_heredoc_mode();
	pid = fork();
	if (!pid)
		write_heredoc(cmd[0], filename);
	else
	{
		sig_heredoc_parent();
		waitpid(pid, status, 0);
		if (g_status == 128 + SIGINT)
			kill(pid, SIGINT);
		if (WIFEXITED(*status))
			set_status(WEXITSTATUS(*status));
		if (WIFSIGNALED(*status))
			set_status(1);//TODO ㅇㅣ부분 확인
		free(cmd[0]);
		cmd[0] = filename;
	}
}

static char	*name_tmp_file(void)
{
	char	*name;
	char	*tmp;
	char	*num_str;
	int		num_file;

	num_file = 1;
	name = ft_strdup("/tmp/heredoc_0");
	while (!access(name, F_OK))
	{
		num_str = ft_itoa(num_file++);
		tmp = ft_strjoin("/tmp/heredoc_", num_str);
		free(num_str);
		free(name);
		name = tmp;
	}
	return (name);
}

static void	write_heredoc(char *delim, char *filename)
{
	char	*str;
	int		len_d;
	int		len_s;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_redir(delim);
	len_d = ft_strlen(delim);
	while (TRUE)
	{
		str = readline("> ");
		if (str)
			len_s = ft_strlen(str);
		if (!str || (len_s == len_d && !ft_strncmp(str, delim, len_d)))
			break ;
		ft_putendl_fd(str, fd);
		free(str);
	}
	if (str != NULL)
		free(str);
	close(fd);
	exit(EXIT_SUCCESS);
}
