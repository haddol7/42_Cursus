/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:27:00 by daeha             #+#    #+#             */
/*   Updated: 2024/06/05 15:28:51 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

int	g_status;

void leaks(void)
{
	system("leaks minishell | grep \"leaks for\"");
}

void print_all_node(t_node *ast, int indent)
{
	if (ast == NULL)
		return ;
	for(int i = 0; i < indent; i++)
		ft_putchar_fd(' ', STDERR_FILENO);
	if(ast->type == N_AND)
		ft_putendl_fd("N_AND", STDERR_FILENO);
	else if (ast->type == N_OR)
		ft_putendl_fd("N_OR", STDERR_FILENO);
	else if (ast->type == N_OUTPUT)
		ft_putendl_fd("N_OUTPUT", STDERR_FILENO);
	else if (ast->type == N_APPEND)
		ft_putendl_fd("N_APPEND", STDERR_FILENO);
	else if (ast->type == N_HERE_DOC)
		ft_putendl_fd("N_HERE_DOC", STDERR_FILENO);
	else if (ast->type == N_INPUT)
		ft_putendl_fd("N_INPUT", STDERR_FILENO);
	else if (ast->type == N_PIPE)
		ft_putendl_fd("N_PIPE", STDERR_FILENO);
	else if (ast->type == N_SUBSHELL)
		ft_putendl_fd("N_SUBSHELL", STDERR_FILENO);
	else
	{
		char	**arg;

		arg = ast->cmd;
		ft_putstr_fd("N_CMD : ", STDERR_FILENO);
		for(int i = 0; arg[i] != NULL; i++)
		{
			dprintf(STDERR_FILENO, "%s ", arg[i]);
		}
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	print_all_node(ast->left, indent + 4);
	print_all_node(ast->right, indent + 4);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	t_token	*token;
	t_node	*ast;
	t_token *head;

	atexit(leaks);
	token = tokenizer(argv[1]);
	head = token;
	printf("\e[32m====================token===================\n");
	print_all_value(token);
	printf("\e[34m====================node====================\n");
	ast = parser(&token);
	print_all_node(ast, 0);
	printf("\e[0mINPUT : %s\n", argv[1]);

	fd[0] = 0;
	fd[1] = 1;
	exec_redir(ast, fd);
	free_tree(&ast);
	return (g_status);
}

/*
	char *str;

	int fd = heredoc(argv[1]);
	str = get_next_line(fd);
	if (str != NULL)
	{
		printf("%s\n", str);
		write(append(argv[2]), str, ft_strlen(str));
	}
*/
