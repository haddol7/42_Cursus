/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:00:07 by daeha             #+#    #+#             */
/*   Updated: 2024/05/28 20:49:01 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	is_token_redir(t_token *token)
{
	if (is_token(token, T_DLESS) || is_token(token, T_DGREAT) || \
		is_token(token, T_LESS) || is_token(token, T_GREAT))
		return (TRUE);
	return (FALSE);
}

t_bool	is_token(t_token *token, t_token_type type)
{
	if (token == NULL)
	{
		ft_putendl_fd("token is NULL!", 2);
		return (FALSE);
	}
	if (token->type == type)
		return (TRUE);
	else
		return (FALSE);
}

void	token_next(t_token **token)
{
	printf("왈루\n");
	
	if ((*token)->type == T_EOF)
		return ;
	if ((*token) == NULL)
		ft_putendl_fd("이런 일은 있을 수 없다고!!!!", STDERR_FILENO);
	*token = (*token)->next;
}
