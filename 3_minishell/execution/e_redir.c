/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:27:02 by daeha             #+#    #+#             */
/*   Updated: 2024/06/24 23:57:19 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "minishell.h"

static t_bool	is_redir_in(t_node_type type);
static t_bool	expansion_and_check_error(t_node *node, t_stat *stat);
static void		make_fd_error(t_node *node, t_stat *stat);

void	exec_redir(t_node *node, t_stat *stat)
{
	if (expansion_and_check_error(node, stat))
		make_fd_error(node, stat);
	else if (stat->fd[INPUT] != -1 && stat->fd[OUTPUT] != -1)
	{
		if (stat->fd[INPUT] != STDIN_FILENO && is_redir_in(node->type))
			close(stat->fd[INPUT]);
		else if (stat->fd[OUTPUT] != STDOUT_FILENO && !is_redir_in(node->type))
			close(stat->fd[OUTPUT]);
		if (node->type == N_INPUT)
			stat->fd[INPUT] = input(node->right->cmd[0]);
		else if (node->type == N_HERE_DOC)
			stat->fd[INPUT] = heredoc(node->right->cmd[0]);
		else if (node->type == N_OUTPUT)
			stat->fd[OUTPUT] = output(node->right->cmd[0]);
		else if (node->type == N_APPEND)
			stat->fd[OUTPUT] = append(node->right->cmd[0]);
	}
	execution(node->left, stat);
}

static t_bool	is_redir_in(t_node_type type)
{
	if (type == N_INPUT || type == N_HERE_DOC)
		return (TRUE);
	return (FALSE);
}

static t_bool	expansion_and_check_error(t_node *node, t_stat *stat)
{
	char	**filename;
	char	*error_str;

	error_str = ft_strdup(node->right->cmd[0]);
	cmd_expansion(node->right, stat->envp);
	filename = node->right->cmd;
	if (filename[0] == NULL || filename[1] != NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(error_str, STDERR_FILENO);
		ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
		set_status(EXIT_FAILURE);
		free(error_str);
		return (TRUE);
	}
	free(error_str);
	return (FALSE);
}

static void	make_fd_error(t_node *node, t_stat *stat)
{
	if (stat->fd[INPUT] != STDIN_FILENO && is_redir_in(node->type))
	{
		close(stat->fd[INPUT]);
		stat->fd[INPUT] = -1;
	}
	else if (stat->fd[OUTPUT] != STDOUT_FILENO && !is_redir_in(node->type))
	{
		close(stat->fd[OUTPUT]);
		stat->fd[OUTPUT] = -1;
	}
}
