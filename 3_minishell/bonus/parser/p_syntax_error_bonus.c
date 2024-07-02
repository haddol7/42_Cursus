/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_syntax_error_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:03:33 by daeha             #+#    #+#             */
/*   Updated: 2024/07/02 17:38:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"
#include "minishell_bonus.h"

static void	syntax_error_type(t_token *token);

void	*syntax_error(t_token *token)
{	
	t_bool	is_error;

	is_error = *get_parser_error();
	if (!is_error)
	{
		if (token->type == T_EOF)
			ft_putendl_fd(SYNTAX_MSG, 2);
		else
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			syntax_error_type(token);
			ft_putendl_fd("'", 2);
		}
		set_status(SYNTAX_ERR);
		set_parser_error(TRUE);
	}
	return (NULL);
}

static void	syntax_error_type(t_token *token)
{
	if (token->type == T_AND_IF)
		ft_putstr_fd("&&", STDERR_FILENO);
	else if (token->type == T_OR_IF)
		ft_putstr_fd("||", STDERR_FILENO);
	else if (token->type == T_GREAT)
		ft_putstr_fd(">", STDERR_FILENO);
	else if (token->type == T_DGREAT)
		ft_putstr_fd(">>", STDERR_FILENO);
	else if (token->type == T_DLESS)
		ft_putstr_fd("<<", STDERR_FILENO);
	else if (token->type == T_LESS)
		ft_putstr_fd("<", STDERR_FILENO);
	else if (token->type == T_PIPE)
		ft_putstr_fd("|", STDERR_FILENO);
	else if (token->type == T_RPAREN)
		ft_putstr_fd(")", STDERR_FILENO);
	else if (token->type == T_LPAREN)
		ft_putstr_fd("(", STDERR_FILENO);
	else if (token->type == T_WORD)
		ft_putstr_fd(token->value, STDERR_FILENO);
}
