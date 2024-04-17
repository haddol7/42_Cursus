/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:15:43 by daeha             #+#    #+#             */
/*   Updated: 2024/04/17 21:18:04 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control_elem.h"
#include "command.h"
#include "deque.h"

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
