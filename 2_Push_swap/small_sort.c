/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:05:19 by daeha             #+#    #+#             */
/*   Updated: 2024/04/15 16:33:23 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"
#include "command.h"

static void	sort_3_to_5(t_total *stack, int size, e_order order);

void sort_small_sort(t_total *stack, int size, e_order order)
{
	int	i;

	i = 0;
	if (size == 1 && order == ASCEND)
		return ;
	else if (size == 2)
	{
		if (order == ASCEND && \ 
			stack->a.top->val > stack->a.top->next->val)
			sa(stack);
		else if (order == DESCEND && \
				 stack->b.top->val < stack->b.top->next->val)
			sb(stack);
	}
	else if (size >= 3)
		sort_3_to_5(stack, size, order);
	if (order == DESCEND)
	{
		while (i < size)
		{
			pa(stack);
			i++;
		}
	}
}

static void	sort_3_to_5(t_total *stack, int size, e_order order)
{
	t_stack	*tmp;
	t_node	*node;
	int		value[5];
	int		i;

	i = -1;
	if (order == ASCEND)
		tmp = &stack->a;
	else
		tmp = &stack->b;
	node = tmp->top;
	while (++i < size)
	{
		value[i] = node->val;
		node = node->next;
	}
	if (size == 3)
		sort_3(stack, size, order, value);
	else if (size == 4)
		sort_4(stack, size, order, value);
	else if (size == 5)
		sort_5(stack, size, order, value);

}
