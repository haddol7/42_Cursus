/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:05:19 by daeha             #+#    #+#             */
/*   Updated: 2024/04/15 18:14:23 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control_elem.h"
#include "deque.h"
#include "command.h"

int	find_max(t_total *stack, int size, e_order order)
{
	t_node 	*node;
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

int	find_min(t_total *stack, int size, e_order order)
{
	t_node 	*node;
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

static void	sort_3_to_5(t_total *stack, int size, e_order order);
static void sort_3(t_total *stack, int size, e_order order);
static void sort_4(t_total *stack, int size, e_order order);
static void sort_5(t_total *stack, int size, e_order order);

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

	if (size == 3)
		sort_3(stack, size, order);
	else if (size == 4)
		sort_4(stack, size, order);
	else
		sort_5(stack, size, order);
}

static void sort_3(t_total *stack, int size, e_order order)
{
	int	max;
	int min;
	
	max = find_max(stack, size, order);
	min = find_min(stack, size, order);
	if (order == ASCEND)
	{
		if (max == stack->a.top->val)
			ra(stack);
		else if (max == stack->a.top->next->val)
			rra(stack);
		if (stack->a.top->val > stack->a.top->next->val)
			sa(stack);
	}
	else
	{
		if (min == stack->b.top->val)
			rb(stack);
		else if (min == stack->b.top->next->val)
			rrb(stack);
		if (stack->b.top->val < stack->b.top->next->val)
			sb(stack);
	}
} 

static void sort_4(t_total *stack, int size, e_order order)
{
	int	cnt;
	int max;
	int min;

	max = find_max(stack, size, order);
	min = find_min(stack, size, order);
	cnt = 0;
	if (order == ASCEND)
	{
		while (stack->a.top->val != max)
		{
			rra(stack);
			cnt++;
		}
		pb(stack);
		sort_3(stack, 3, order);
		pa(stack);
		ra(stack);
	}
	else
	{
		while (stack->b.top->val != min)
		{
			ra(stack);
			cnt++;
		}
		pa(stack);
		sort_3(stack, 3, order);
		pb(stack);
		rb(stack);
	}
} 
 
static void sort_5(t_total *stack, int size, e_order order)
{
	
}
