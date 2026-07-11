/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:00:07 by daeha             #+#    #+#             */
/*   Updated: 2024/06/18 00:20:38 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*free_simple_command(char **arg, t_node *redir)
{
	if (arg != NULL)
		free_arg(&arg);
	if (redir != NULL)
		free_all_tree(&redir);
	return (NULL);
}

t_bool	is_token_redir(t_token *token)
{
	if (is_token(token, T_DLESS) || is_token(token, T_DGREAT) || \
		is_token(token, T_LESS) || is_token(token, T_GREAT))
	{
		return (TRUE);
	}
	return (FALSE);
}

t_bool	is_token(t_token *token, t_token_type type)
{
	if (token == NULL)
		return (FALSE);
	else if (token->type == type)
		return (TRUE);
	else
		return (FALSE);
}

void	token_next(t_token **token)
{
	if (*token == NULL || (*token)->type == T_EOF)
		return ;
	*token = (*token)->next;
}
