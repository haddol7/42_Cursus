/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:48:37 by daeha             #+#    #+#             */
/*   Updated: 2024/05/30 14:08:20 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node *parser(t_token **token)
{
	t_node	*ast;
	if (!is_token(*token, T_EOF))
	{
		ast = list(token);
		if (!(is_token(*token, T_EOF)))
		{
			syntax_error_test(*token);
			//free_ast_node(ast);
			//setsignal_error
			printf("너는 문법을 지키지 않았어.\n");
			return (NULL);
		}
	}
	else
		return (NULL);
	return (ast);
}
