/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:27:00 by daeha             #+#    #+#             */
/*   Updated: 2024/06/24 21:07:08 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

static void	init_stat(t_stat *stat);
static void	display_title(int argc, char **argv);
static void	loop_prompt(t_minishell *ms);
static void	close_all_fds(t_stat *stat);

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	display_title(argc, argv);
	ms.stat.envp = init_env_list(envp);
	loop_prompt(&ms);
	env_free_all(&ms.stat.envp);
	return (g_status);
}

static void	loop_prompt(t_minishell *ms)
{
	char			*input;
	static int		pre_status;

	input = "";
	while (input)
	{	
		sig_prompt_mode();
		input = readline("minishell$ ");
		if (input)
		{
			init_stat(&ms->stat);
			add_history_if_not_null(input);
			ms->token = tokenizer(input);
			ms->ast = parser(ms->token);
			exec_here_doc(ms->ast);
			execution_no_sig(ms->ast, &ms->stat);
			wait_pid_list(&ms->stat);
			free_all_nodes(ms);
			save_status(&pre_status);
			close_all_fds(&ms->stat);
			free(input);
		}
	}
	clear_history();
	write(STDOUT_FILENO, "exit\n", 5);
}

static void	init_stat(t_stat *stat)
{
	stat->fd[INPUT] = STDIN_FILENO;
	stat->fd[OUTPUT] = STDOUT_FILENO;
	stat->n_pid = 0;
	stat->n_pipe = 0;
	stat->is_pipe = 0;
}

static void	close_all_fds(t_stat *stat)
{	
	if (stat->fd[INPUT] != STDIN_FILENO)
		close(stat->fd[INPUT]);
	if (stat->fd[OUTPUT] != STDOUT_FILENO)
		close(stat->fd[OUTPUT]);
}

static void	display_title(int argc, char **argv)
{
	if (argc > 1 && !ft_strcmp(argv[1], "-s"))
		return ;
	printf("\033[0;32m");
	printf("  _____ _   _                __           _                  \n");
	printf(" |_   _| | ( )              / _|         | |                 \n");
	printf("   | | | |_|/ ___    __ _  | |_ ___  __ _| |_ _   _ _ __ ___ \n");
	printf("   | | | __| / __|  / _` | |  _/ _ \\/ _` | __| | | | '__/ _ \\\n");
	printf("  _| |_| |_  \\__ \\ | (_| | | ||  __| (_| | |_| |_| | | |  __/\n");
	printf(" |_____\\___| |___/  \\__,_| |_| \\___|\\__,_|\\__|\\__,_|_|  \\___|\n\n");
	printf("\033[0m");
}
/*
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
*/
