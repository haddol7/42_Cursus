/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:50:09 by daeha             #+#    #+#             */
/*   Updated: 2024/06/06 18:08:59 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "execution.h"

void	exec_here_doc(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == N_HERE_DOC)
		proc_here_doc(node->cmd);
	exec_here_doc(node->left);
	exec_here_doc(node->right);
}

static char	*name_tmp_file()
{
	char	*name;
	char	*tmp;
	
	name = ft_strdup(TMP_FILE_NAME);
	while (!access(name, F_OK))
	{
		tmp = ft_strjoin(name, ".tmp");
		free(name);
		name = tmp;
	}
	return (name);
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
		if (!str || (len_s == len_d + 1 && !ft_strncmp(str, delim, len_d)))
			break ;
		write(fd, str, len_s);
		free(str);
	}
	if (str != NULL)
		free(str);
	close(fd);
}
