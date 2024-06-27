/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redir_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:50:09 by daeha             #+#    #+#             */
/*   Updated: 2024/06/27 16:03:15 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

static void	proc_here_doc(char **cmd, t_env *envp);
static void	write_heredoc(char *delim, char *filename, t_env *envp);
static char	*name_tmp_file(void);
static char	*delim_expand_quote(char *delim);

extern int	g_signal;

void	exec_here_doc(t_node *node, t_env *envp)
{
	if (g_signal == SIGINT)
		return ;
	if (node == NULL || node->type == N_CMD)
		return ;
	if (node->type == N_HERE_DOC)
		proc_here_doc(node->right->cmd, envp);
	exec_here_doc(node->left, envp);
	exec_here_doc(node->right, envp);
}

static void	proc_here_doc(char **cmd, t_env *envp)
{
	pid_t	pid;
	char	*filename;
	int		*status;

	status = get_status();
	filename = name_tmp_file();
	sig_heredoc_mode();
	pid = fork();
	if (!pid)
		write_heredoc(cmd[0], filename, envp);
	else
	{
		sig_heredoc_parent();
		waitpid(pid, status, 0);
		if (g_signal == SIGINT)
			kill(pid, SIGINT);
		if (WIFEXITED(*status))
			set_status(WEXITSTATUS(*status));
		if (WIFSIGNALED(*status))
			set_status(1);
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

static char	*delim_expand_quote(char *delim)
{
	int		i;
	char	*word_tmp;

	i = 0;
	word_tmp = 0;
	while (delim[i] != '\0')
	{
		if (delim[i] == '\'' || delim[i] == '\"')
			word_tmp = de_quote(delim, &i, word_tmp, delim[i]);
		else
			word_tmp = no_quote(delim, &i, word_tmp);
	}
	free(delim);
	return (word_tmp);
}

static void	write_heredoc(char *delim, char *filename, t_env *envp)
{
	char	*str;
	int		len_d;
	int		len_s;
	int		fd;

	delim = delim_expand_quote(delim);
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
		str = expand_dollar_here_doc(str, envp);
		ft_putendl_fd(str, fd);
		free(str);
	}
	if (str != NULL)
		free(str);
	close(fd);
	exit(EXIT_SUCCESS);
}
