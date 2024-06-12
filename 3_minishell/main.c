/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:27:00 by daeha             #+#    #+#             */
/*   Updated: 2024/06/12 18:32:27 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

int	g_status;

void	leaks(void)
{
	system("leaks minishell | grep \"leaks for\"");
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

int	is_nothing(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	print_all_env(t_env *head)//TODO ㅈㅣ우ㅓ
{
	t_env	*to_print;
	int		i;

	to_print = head;
	i = 1;
	while (to_print != NULL)
		to_print = to_print->next;
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int	main(int argc, char **argv, char **envp)
{
	t_stat	stat;
	t_token	*token;
	t_node	*ast;
	t_env	*env;

	char	*input;

	// env = malloc(sizeof(t_env));
	env = env_cpy(envp);
	print_all_env(env);
	input = "";
	while (input)
	{
		input = readline("> ");
		if (*input)
		{
			stat.fd[0] = 0;
			stat.fd[1] = 1;
			stat.n_pid = 0;
			stat.n_pipe = 0;
			add_history(input);
			token = tokenizer(input);
			ast = parser(token);
			expansion(ast, env);
			exec_here_doc(ast);
			// print_all_value(token);
			//print_all_node(ast, 0, input);
      		execution(ast, &stat);
			ms_free_all_token(&token);
			wait_pid_list(&stat);
			free_tree(&ast);
			free(input);
		}
	}
	rl_clear_history();
	env_free_all(&env);
	return (g_status);
}

