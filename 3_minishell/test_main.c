/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:15:31 by daeha             #+#    #+#             */
/*   Updated: 2024/05/30 19:15:33 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	print_all_node(t_node *ast, int indent)
{
	if (ast == NULL)
		return ;

	for(int i = 0; i < indent; i++)
		ft_putchar_fd(' ', STDERR_FILENO);
	if (ast->type == N_AND)
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
		ft_putendl_fd("N_PIPE", STDERR_FILENO);
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

void	leaks(void)
{
	system("leaks minishell | grep 'leaks for'");
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token;
	t_token *head;
	t_node	*ast;

	atexit(leaks);
	token = tokenizer(argv[1]);
	head = token;
	print_all_value(token);
	printf("=====token====\n");
	ast = parser(&token);
	printf("minishell > %s\n", argv[1]);
	printf("=====node====\n");
	print_all_node(ast, 0);
	free_tree(&ast);
	return (0);
}
