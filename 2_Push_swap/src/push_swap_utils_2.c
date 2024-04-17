/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:15:43 by daeha             #+#    #+#             */
/*   Updated: 2024/04/17 22:51:59 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control_elem.h"
#include "command.h"
#include "deque.h"

void	ps_count_command(t_total *stack, void (*command)(t_total *), int *cnt)
{
	command(stack);
	(*cnt)++;
}

int	ps_find_max(t_total *stack, int size, e_order order)
{
	t_node	*node;
	int		result;

	if (order == ASCEND)
		node = stack->a.top;
	else
		node = stack->b.top;
	result = node->val;
	while (size--)
	{
		if (node->val > result)
			result = node->val;
		node = node->next;
	}
	return (result);
}

int	ps_find_min(t_total *stack, int size, e_order order)
{
	t_node	*node;
	int		result;

	if (order == ASCEND)
		node = stack->a.top;
	else
		node = stack->b.top;
	result = node->val;
	while (size--)
	{
		if (node->val < result)
			result = node->val;
		node = node->next;
	}
	return (result);
}

int	ps_is_stack_sorted(t_total *stack, int size, e_order sort)
{
	int		i;
	t_node	*node;

	i = 0;
	if (sort == ASCEND)
		node = stack->a.top;
	else
		node = stack->b.top;
	while (++i < size)
	{	
		if (sort == ASCEND && node->val > node->next->val)
			return (0);
		else if (sort == DESCEND && node->val < node->next->val)
			return (0);
		node = node->next;
	}
	if (sort == DESCEND)
	{
		i = -1;
		while (++i < size)
			pa(stack);
	}
	return (1);
}
