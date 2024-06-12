/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:27:00 by daeha             #+#    #+#             */
/*   Updated: 2024/06/12 22:28:17 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

static void	init_stat(t_stat *stat);

//TODO: 환경변수가 다 지워졌을 때, unset으로 다 지웠을 때를 생각!
int	main(int argc, char **argv, char **envp)
{
	t_node	*ast;
	t_token	*token;
	t_stat	stat;
	char	*input;

	if (argc > 0)
		argv[0] = 0;
	stat.envp = env_cpy(envp);
	input = "";
	while (input)
	{
		input = readline("minishell$ ");
		if (*input)
		{
			init_stat(&stat);
			add_history(input);
			token = tokenizer(input);
			ast = parser(token);
			expansion(ast, stat.envp);
			exec_here_doc(ast);
      		execution(ast, &stat);
			wait_pid_list(&stat);
			free_all_token(&token);
			free_all_tree(&ast);
			free(input);
		}
	}
	rl_clear_history();
	env_free_all(&stat.envp);
	return (g_status);
}

static void	init_stat(t_stat *stat)
{
	stat->fd[INPUT] = STDIN_FILENO;
	stat->fd[OUTPUT] = STDOUT_FILENO;
	stat->n_pid = 0;
	stat->n_pipe = 0;
}

void	print_all_value(t_token *head)
{
	t_token	*to_print;

	to_print = head;
	if (!head)
		return ;
	printf("\e[32m====================token===================\n");
	while (to_print->type != T_EOF)
	{
		if (to_print->type == T_WORD)
			printf("T_WORD : ");
		if (to_print->type == T_PIPE)
			printf("T_PIPE : ");
		if (to_print->type == T_DLESS)
			printf("T_DLESS : ");
		if (to_print->type == T_DGREAT)
			printf("T_DGREAT : ");
		if (to_print->type == T_LESS)
			printf("T_LESS : ");
		if (to_print->type == T_GREAT)
			printf("T_GREAT : ");
		if (to_print->type == T_LPAREN)
			printf("T_LPAREN : ");
		if (to_print->type == T_RPAREN)
			printf("T_RPAREN : ");
		if (to_print->type == T_AND_IF)
			printf("T_AND_IF : ");
		if (to_print->type == T_OR_IF)
			printf("T_OR_IF : ");
		if (to_print->type != T_EOF)
			printf("%s\n", to_print->value);
		to_print = to_print->next;
	}
	printf("\e[0m");
}

void	print_all_node(t_node *ast, int indent, char *input)
{
	char	**arg;

	if (ast == NULL)
	{
		printf("\e[0m");
		return ;
	}
	else if (indent == 0)
	{
		printf("\n\e[34m====================node====================\n");
	}
	for(int i = 0; i < indent; i++)
	{
		ft_putchar_fd(' ', STDERR_FILENO);
	}
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
		arg = ast->cmd;
		ft_putstr_fd("N_CMD : ", STDERR_FILENO);
		for(int i = 0; arg && arg[i] != NULL; i++)
		{
			dprintf(STDERR_FILENO, "%s, ", arg[i]);
		}
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	print_all_node(ast->left, indent + 4, input);
	print_all_node(ast->right, indent + 4, input);
	if (indent == 0)
		printf("\e[31m> %s\e[0m\n\n", input);
}

