/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:05:19 by daeha             #+#    #+#             */
/*   Updated: 2024/04/15 17:22:17 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control_elem.h"
#include "deque.h"
#include "command.h"

int	find_max(int *ary, int size)
{
	int	i;
	int	result;

	i = 1;
	result = ary[0];
	while (i < size)
	{
		if (ary[i] > result)
			result = ary[i];
		i++;
	}
	return (result);
}

int	find_min(int *ary, int size)
{
	int	i;
	int	result;

	i = 1;
	result = ary[0];
	while (i < size)
	{
		if (ary[i] < result)
			result = ary[i];
		i++;
	}
	return (result);
}

static void	sort_3_to_5(t_total *stack, int size, e_order order);
static void sort_3(t_total *stack, int size, e_order order, int *value);
static void sort_4(t_total *stack, int size, e_order order, int *value);
static void sort_5(t_total *stack, int size, e_order order, int *value);

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
	else
		sort_5(stack, size, order, value);
}

static void sort_3(t_total *stack, int size, e_order order, int *value)
{
	int	max;
	int min;
	
	max = find_max(value, size);
	min = find_min(value, size);


	if (max == value[0] && order == ASCEND)
		ra(stack);
	else if (max == value[1] && order == ASCEND)
		rra(stack);
	if (order == ASCEND && stack->a.top->val > stack->a.top->next->val)
		sa(stack);
	if (order == DESCEND && min == value[0])
		rb(stack);
	else if (min == value[1] && order == DESCEND)
		rrb(stack);
	if (order == DESCEND && stack->b.top->val < stack->b.top->next->val)
		sb(stack);
} 

static void sort_4(t_total *stack, int size, e_order order, int *value)
{
	
} 
 
static void sort_5(t_total *stack, int size, e_order order, int *value)
{
	
}
