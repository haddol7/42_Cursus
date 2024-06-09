/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_type_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:12:40 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/09 17:13:31 by daeha            ###   ########.fr       */
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

int	check_if_terminal(char c1, char c2)
{
	if (c1 != '\0' && \
		c1 != ' ' && c1 != '|' && \
		c1 != '<' && c1 != '>' && \
		c1 != '(' && c1 != ')' && \
		!(c1 == '&' && c2 == '&') && \
		!(c1 == '|' && c2 == '|')
	)
		return (0);
	else
		return (1);
}

int	input_word(t_token **head, char *input, int *idx)
{
	t_token	*node;
	char	*value;
	int		len;
	int		start;
	int		quote;

	len = 1;
	start = *idx;
	quote = 0;
	while (check_if_terminal(input[start + len], input[start + len + 1]) == 0)
	{
		if (input[start + len] == '\'' || input[start + len] == '\"')
			quote++;
		len++;
	}
	if (quote % 2 != 0)
		return (handle_error("bash: unexpected EOF while looking for matching quote\n", 0, head));
	value = (char *)malloc(sizeof(char) * (len + 1));
	if (value == NULL)
		handle_error("exit : malloc error", 1, 0);
	ft_strlcpy(value, (const char *)(input + start), len + 1);
	node = ms_lstnew(value, T_WORD);
	ms_lstadd_back(head, node);
	*idx = start + len;
	return (1);
}
