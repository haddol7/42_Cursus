/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:00:07 by daeha             #+#    #+#             */
/*   Updated: 2024/06/04 17:16:26 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
