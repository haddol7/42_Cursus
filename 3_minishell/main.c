/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:27:00 by daeha             #+#    #+#             */
/*   Updated: 2024/05/30 00:09:55 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

static int	g_status;

void print_all_node(t_node *ast, int indent, int is_leaf)
{
	if (ast == NULL)
		return ;
	
	for(int i = 0; i < indent; i++)
	{
		if (i && i % 4 == 0)
			dprintf(2, "┃");
		ft_putchar_fd(' ', STDERR_FILENO);
	}
	if (is_leaf == 1)
		dprintf(2, "┗");
	else if (is_leaf == 2)
		dprintf(2, "┏");

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
	if (ast->left && ast->right)
		is_leaf = 1;
	else
		is_leaf = 0;
	print_all_node(ast->left, indent + 4, is_leaf * 2);
	print_all_node(ast->right, indent + 4, is_leaf);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token;
	t_node	*ast;

	token = tokenizer(argv[1]);
	print_all_value(token);
	printf("=====token====\n");
	ast = parser(&token);
	printf("minishell > %s\n", argv[1]);
	printf("=====node====\n");
	print_all_node(ast, 0, 0);

	return (0);
}

