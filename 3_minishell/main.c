/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:27:00 by daeha             #+#    #+#             */
/*   Updated: 2024/05/30 14:24:27 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_token	*token;
	t_node	*ast;
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		token = tokenizer(line);
		print_all_value(token);
		printf("=====token====\n");
		ast = parser(&token);
		printf("=====node====\n");
		print_all_node(ast, 0, 0);
		ms_free_all_token(&token);
		//free_ast();
		free(line);
		line = NULL;
		token = NULL;
	}
	return (0);
}
