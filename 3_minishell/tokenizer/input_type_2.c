/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_type_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:12:40 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/17 18:21:32 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	input_paren(t_token **head, char input, int *idx)
{
	t_token_type	type;
	char			*value;
	t_token			*node;

	if (input == '(')
		type = T_LPAREN;
	else
		type = T_RPAREN;
	value = (char *)malloc(sizeof(char) * 2);
	if (value == NULL)
		handle_error("exit : malloc error", 1, 0);
	value[0] = input;
	value[1] = '\0';
	node = ms_lstnew(value, type);
	ms_lstadd_back(head, node);
	*idx = *idx + 1;
}

void	input_and_if(t_token **head, int *idx)
{
	t_token	*node;
	char	*value;

	value = ft_strdup("&&");
	if (value == NULL)
		handle_error("exit : malloc error", 1, 0);
	node = ms_lstnew(value, T_AND_IF);
	ms_lstadd_back(head, node);
	*idx = *idx + 2;
}

void	input_or_if(t_token **head, int *idx)
{
	t_token	*node;
	char	*value;

	value = ft_strdup("||");
	if (value == NULL)
		handle_error("exit : malloc error", 1, 0);
	node = ms_lstnew(value, T_OR_IF);
	ms_lstadd_back(head, node);
	*idx = *idx + 2;
}
