/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:39:36 by daeha             #+#    #+#             */
/*   Updated: 2024/06/17 18:48:30 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

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

// void	print_all_value(t_token *head)
// {
// 	t_token	*to_print;

// 	to_print = head;
// 	if (!head)
// 		return ;
// 	printf("\e[32m====================token===================\n");
// 	while (to_print->type != T_EOF)
// 	{
// 		if (to_print->type == T_WORD)
// 			printf("T_WORD : ");
// 		if (to_print->type == T_PIPE)
// 			printf("T_PIPE : ");
// 		if (to_print->type == T_DLESS)
// 			printf("T_DLESS : ");
// 		if (to_print->type == T_DGREAT)
// 			printf("T_DGREAT : ");
// 		if (to_print->type == T_LESS)
// 			printf("T_LESS : ");
// 		if (to_print->type == T_GREAT)
// 			printf("T_GREAT : ");
// 		if (to_print->type == T_LPAREN)
// 			printf("T_LPAREN : ");
// 		if (to_print->type == T_RPAREN)
// 			printf("T_RPAREN : ");
// 		if (to_print->type == T_AND_IF)
// 			printf("T_AND_IF : ");
// 		if (to_print->type == T_OR_IF)
// 			printf("T_OR_IF : ");
// 		if (to_print->type != T_EOF)
// 			printf("%s\n", to_print->value);
// 		to_print = to_print->next;
// 	}
// 	printf("\e[0m");
// }