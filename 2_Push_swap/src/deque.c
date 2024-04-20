/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:40:25 by daeha             #+#    #+#             */
/*   Updated: 2024/04/21 00:51:11 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

void	push(t_stack *stack, t_node *node, t_pos pos)
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

t_node	*pop(t_stack *stack, t_pos pos)
{
	t_node	*node;

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
		if (stack->size > 1)
		{
			stack->bot->next = stack->top;
			stack->top->prev = stack->bot;
		}
	}
	stack->size--;
	return (node);
}

void	node_swap(t_stack *stack)
{
	t_node	*temp;
	t_node	*temp2;

	temp = pop(stack, TOP);
	temp2 = pop(stack, TOP);
	push(stack, temp, TOP);
	push(stack, temp2, TOP);
}
