/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:05:19 by daeha             #+#    #+#             */
/*   Updated: 2024/04/16 19:44:29 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control_elem.h"
#include "command.h"

static void swap_int(int *a, int *b)
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

int	find_max(t_total *stack, int size)
{
	t_node 	*node;
	int		result;

	node = stack->a.top;
	result = node->val;
	while (size--)
	{
		if (node->val > result)
			result = node->val;
		node = node->next;
	}
	return (result);
}

int	find_min(t_total *stack, int size)
{
	t_node 	*node;
	int		result;

	node = stack->a.top;
	result = node->val;
	while (size--)
	{
		if (node->val < result)
			result = node->val;
		node = node->next;
	}
	return (result);
}

static void sort_3(t_total *stack);
static void sort_4(t_total *stack);
static void sort_5(t_total *stack);

void sort_small_sort(t_total *stack, int size)
{
	if (size == 1)
		return ;
	else if (size == 2)
	{
		if (stack->a.top->val > stack->a.top->next->val)
			sa(stack);
	}
	else if (size == 3)
		sort_3(stack);
	else if (size == 4)
		sort_4(stack);
	else
		sort_5(stack);
}

static void sort_3(t_total *stack)
{
	int	max;
	int min;
	
	max = find_max(stack, 3);
	min = find_min(stack, 3);
	if (max == stack->a.top->val)
		ra(stack);
	else if (max == stack->a.top->next->val)
		rra(stack);
	if (stack->a.top->val > stack->a.top->next->val)
		sa(stack);
} 

int	find_idx(t_total *stack, int value)
{
	int idx;
	t_node	*node;
	
	idx = 0;
	node = stack->a.top;
	while (node->val != value)
	{
		node = node->next;
		idx++;
	}
	return (idx);
}

static void sort_4(t_total *stack)
{
	int	cnt;
	int max;
	int idx;

	max = find_max(stack, 4);
	idx = find_idx(stack, max);
	cnt = 0;
	while (stack->a.top->val != max)
	{	
		if (idx < 2)
			ra(stack);
		else
			rra(stack);
		cnt++;
	}
	pb(stack);
	sort_3(stack);
	pa(stack);
	ra(stack);
} 
 
void test(t_stack stack, int *min_1, int *min_2)
{
	int		ary[5];
	t_node	*temp;

	temp = stack.top;

	for (int i = 0; i < 5; i++)
	{
		ary[i] = temp->val;
		temp = temp->next;
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5 - i - 1; j++)
		{
			if (ary[j] > ary[j + 1])
				swap_int(ary + j, ary + j + 1);
		}
	}
	*min_1 = ary[0];
	*min_2 = ary[1];
}

static void sort_5(t_total *stack)
{
	int	cnt;
	int max;
	int idx;
	int idx_2;
	
	int min1;
	int min2;
	
	test(stack->a, &min1, &min2);
	while (cnt < 2)
	{
		if (stack->a.top->val == 1 || stack->a.top->val == 2)
		{
			pb(stack);
			cnt++;
		}
		rra(stack);
	}
	sort_3(stack);
	if (stack->b.top->val < stack->b.bot->val)
		sb(stack);
	pa(stack);
	pa(stack);
}
