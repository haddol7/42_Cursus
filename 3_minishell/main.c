/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:27:00 by daeha             #+#    #+#             */
/*   Updated: 2024/06/09 17:58:55 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

int	g_status;

void print_all_node(t_node *ast, int indent, int is_leaf)
{
	char	**arg;
	
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
		arg = ast->cmd;
		ft_putstr_fd("N_CMD : ", STDERR_FILENO);
		for(int i = 0; arg[i] != NULL; i++)
		{
			dprintf(STDERR_FILENO, "%s,  ", arg[i]);
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
	t_token	*token;
	t_node	*ast;
	char	*line;
	t_env	*env;

	env_cpy(&env, envp);
	// print_all_env(env);
	while (1)
	{
		line = readline("minishell> ");
		if (is_nothing(line) == 1)
		{
			free(line);
			continue ;
		}
		add_history(line);
		token = tokenizer(line);
		print_all_value(token);
		printf("=====token====\n");
		ast = parser(&token);
		// printf("minishell >> %s\n", line);
		printf("=====node====\n");
		// print_all_node(ast, 0, 0);
		check_cmd_node(ast, env);
		print_all_node(ast, 0, 0);//TODO 왜 이거에서 에러가 나지??
		ms_free_all_token(&token);
		//free_ast();
		free(line);
		line = NULL;
		token = NULL;
	}
	rl_clear_history();
	env_free_all(&env);
	return (0);
}
