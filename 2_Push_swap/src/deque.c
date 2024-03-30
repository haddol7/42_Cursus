/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:40:25 by daeha             #+#    #+#             */
/*   Updated: 2024/03/30 23:38:59 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/deque.h"

/*
sa	|	node_swap(&a);
sb 	|	node_swap(&b);
ss 	|	node_swap(&a) && node_swap(&b)
pa 	|	push(&a, pop(&b, TOP), TOP);
pb 	|	push(&b, pop(&a, TOP), TOP);
ra 	|	push(&a, pop(&a, TOP), BOT);
rb 	|	push(&b, pop(&b, TOP), BOT);
rr 	|	ra && rb
rra |	push(&a, pop(&a, BOT), TOP);
rrb |	push(&b, pop(&b, BOT), TOP);
rrr |	rra && rrb
*/

void	push(t_stack *stack, t_node *node, e_pos pos)
{
	if (node == NULL)
		return ;
	if (stack->size == 0)
	{
		stack->bot = node;
		stack->top = node;
	}
	else
	{
		node->prev = stack->bot;
		node->next = stack->top;
		stack->bot->next = node;
		stack->top->prev = node;
		if (pos == TOP)
			stack->top = node;
		else
			stack->bot = node;
	}
	stack->size++;
}

t_node	*pop(t_stack *stack, e_pos pos)
{
	t_node *node;
	
	if (stack->size == 0)
		return (NULL);
	else
	{
		if (pos == TOP)
		{
			node = stack->top;
			stack->top = node->next;
		}
		else
		{
			node = stack->bot;
			stack->bot = node->prev;
		}
		stack->bot->next = stack->top;
		stack->top->prev = stack->bot;
	}
	stack->size--;
	return (node);
}

void top_swap(t_stack *stack)
{
	t_node *temp;
	t_node *temp2;

	temp = pop(stack, TOP);
	temp2 = pop(stack, TOP);
	push(stack, temp, TOP);
	push(stack, temp2, TOP);
}

