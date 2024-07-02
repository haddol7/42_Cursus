/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_type_2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:12:40 by jungslee          #+#    #+#             */
/*   Updated: 2024/07/02 17:38:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_bonus.h"

void	input_paren(t_token **head, char input, int *idx)
{
	t_token_type	type;
	char			*value;
	t_token			*node;

	if (input == '(')
		type = T_LPAREN;
	else
		type = T_RPAREN;
	value = (char *)ft_malloc(sizeof(char) * 2);
	value[0] = input;
	value[1] = '\0';
	node = ms_lstnew(value, type);
	ms_lstadd_back(head, node);
	*idx = *idx + 1;
}

int	input_and_if(t_token **head, char *input, int *idx)
{
	t_token	*node;
	char	*value;

	if (input[*idx + 2] == '&')
		return (handle_error(ERR_AND_IF, 0, head));
	value = ft_strdup("&&");
	if (value == NULL)
		handle_error("exit : malloc error", 1, 0);
	node = ms_lstnew(value, T_AND_IF);
	ms_lstadd_back(head, node);
	*idx = *idx + 2;
	return (1);
}

int	input_or_if(t_token **head, char *input, int *idx)
{
	t_token	*node;
	char	*value;

	if (input[*idx + 2] == '|')
		return (handle_error(ERR_OR_IF, 0, head));
	value = ft_strdup("||");
	node = ms_lstnew(value, T_OR_IF);
	ms_lstadd_back(head, node);
	*idx = *idx + 2;
	return (1);
}
