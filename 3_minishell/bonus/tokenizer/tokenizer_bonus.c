/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:39:36 by daeha             #+#    #+#             */
/*   Updated: 2024/06/19 23:22:25 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_bonus.h"

int	detect_type(t_token **head, char *input, int *i)
{
	if (input[*i] == '|' && input[*i + 1] != '|')
		input_pipe(head, i);
	else if (input[*i] == '<' || input[*i] == '>')
		input_redirection(head, input, i);
	else if (input[*i] == '(' || input[*i] == ')')
		input_paren(head, input[*i], i);
	else if (input[*i] == '&' && input[*i + 1] == '&')
		input_and_if(head, i);
	else if (input[*i] == '|' && input[*i + 1] == '|')
		input_or_if(head, i);
	else if (input[*i] == ' ')
		(*i)++;
	else
	{
		if (input_word(head, input, i) == 0)
			return (0);
	}
	return (1);
}

t_token	*tokenizer(char *input)
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	if (input == 0 || *input == '\0')
		return (0);
	while (input[i] != '\0')
	{
		if (detect_type(&head, input, &i) == 0)
			return (0);
	}
	eof_node(&head);
	return (head);
}
