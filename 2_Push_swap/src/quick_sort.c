/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:56:31 by daeha             #+#    #+#             */
/*   Updated: 2024/04/16 16:54:52 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control_elem.h"
#include "command.h"
#include "deque.h"

static int	find_max(t_total *stack, int size, e_order order)
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

static int	find_min(t_total *stack, int size, e_order order)
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

int	is_sorted(t_total *stack, int size, e_order sort)
{
	int		i;
	t_node	*node;

	if (sort == ASCEND)
		node = stack->a.top;
	else
		node = stack->b.top;
	i = 1;
	while (i < size)
	{	
		if (sort == ASCEND && node->val > node->next->val)
			return (0);
		else if (sort == DESCEND && node->val < node->next->val)
			return (0);
		node = node->next;
		i++;
	}
	if (sort == DESCEND)
	{
		i = 0;
		while (i < size)
		{
			pa(stack);
			i++;
		}
	}
	return (1);
}

void swap_int(int *a, int *b)
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void	set_pivot(t_stack stack, int size, int *pivot_1, int *pivot_2, e_order order)
{
	int		*ary;
	int		pivot;
	t_node	*temp;

	ary = malloc(sizeof(int) * size);
	temp = stack.top;

	for (int i = 0; i < size; i++)
	{
		ary[i] = temp->val;
		temp = temp->next;
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (ary[j] > ary[j + 1])
				swap_int(ary + j, ary + j + 1);
		}
	}
	if (order == ASCEND)
	{
		*pivot_2 = ary[(size - 1) - (size / 3) * 2];
		*pivot_1 = ary[(size - 1) - (size / 3 - 1)];
	}
	else
	{
		*pivot_2 = ary[size / 3 - 1];
		*pivot_1 = ary[(size / 3) * 2];
	}
	free(ary);

}
void A_to_B(t_total *stack, int size);
static void B_to_A(t_total *stack, int size);

void initial(t_total *stack, int size)
{
	int pivot_1;
	int pivot_2;
	int cnt_ra;
	int cnt_pb;
	int cnt_rb;
	int val;
	
	cnt_ra = 0;
	cnt_pb = 0;
	cnt_rb = 0;
	if (size == 1)
		return;
	if (size == 2)
	{
		if (stack->a.top->val > stack->a.top->next->val)
			sa(stack);
		return ;
	}
	if (is_sorted(stack, size, ASCEND))
		return ;
	if (size == 3)
	{
		int max = find_max(stack, 3, ASCEND);
		int min = find_min(stack, 3, ASCEND);

		int one = stack->a.top->val;
		int two = stack->a.top->next->val;
		int three = stack->a.top->next->next->val;

		if (min == one && max == two)
		{
			pb(stack);
			sa(stack);
			pa(stack);
		}
		else if (min == two && max == three)
		{
			sa(stack);
		}
		else if (min == two && max == one)
		{
			sa(stack);
			pb(stack);
			sa(stack);
			pa(stack);
		}
		else if (min == three && max == one)
		{
			sa(stack);
			ra(stack);
			ra(stack);
			pb(stack);
			rra(stack);
			rra(stack);
			pa(stack);
		}
		else if (min == three && max == two)
		{
			ra(stack);
			ra(stack);
			pb(stack);
			rra(stack);
			rra(stack);
			pa(stack);
		}
		return;
	}
	set_pivot(stack->a, size, &pivot_1, &pivot_2, ASCEND);
	for (int i = 0; i < size ; i++)
	{
		val = stack->a.top->val;
		if (val >= pivot_1)
		{
			ra(stack);
			cnt_ra++;
		}
		else
		{
			pb(stack);
			cnt_pb++;
			if (val <= pivot_2)
			{
				rb(stack);
				cnt_rb++;
			}
		}
	}

	A_to_B(stack, cnt_ra);
	B_to_A(stack, cnt_pb - cnt_rb);
	B_to_A(stack, cnt_rb);
}

void A_to_B(t_total *stack, int size)
{
	int pivot_1;
	int pivot_2;
	int cnt_ra;
	int cnt_pb;
	int cnt_rb;
	int val;
	
	cnt_ra = 0;
	cnt_pb = 0;
	cnt_rb = 0;
	if (size == 1)
		return;
	if (size == 2)
	{
		if (stack->a.top->val > stack->a.top->next->val)
			sa(stack);
		return ;
	}
	if (is_sorted(stack, size, ASCEND))
		return ;
	if (size == 3)
	{
		int max = find_max(stack, 3, ASCEND);
		int min = find_min(stack, 3, ASCEND);

		int one = stack->a.top->val;
		int two = stack->a.top->next->val;
		int three = stack->a.top->next->next->val;

		if (min == one && max == two)
		{
			pb(stack);
			sa(stack);
			pa(stack);
		}
		else if (min == two && max == three)
		{
			sa(stack);
		}
		else if (min == two && max == one)
		{
			sa(stack);
			pb(stack);
			sa(stack);
			pa(stack);
		}
		else if (min == three && max == one)
		{
			sa(stack);
			ra(stack);
			ra(stack);
			pb(stack);
			rra(stack);
			rra(stack);
			pa(stack);
		}
		else if (min == three && max == two)
		{
			ra(stack);
			ra(stack);
			pb(stack);
			rra(stack);
			rra(stack);
			pa(stack);
		}
		return;
	}
	set_pivot(stack->a, size, &pivot_1, &pivot_2, ASCEND);
	for (int i = 0; i < size ; i++)
	{
		val = stack->a.top->val;
		if (val >= pivot_1)
		{
			ra(stack);
			cnt_ra++;
		}
		else
		{
			pb(stack);
			cnt_pb++;
			if (val > pivot_2)
			{
				rb(stack);
				cnt_rb++;
			}
		}
	}
	int j = 0;
	while (j < cnt_rb || j < cnt_ra)
	{
		if (j < cnt_rb && j < cnt_ra)
			rrr(stack);
		else if (j < cnt_rb)
			rrb(stack);
		else
			rra(stack);
		j++;
	}
	A_to_B(stack, cnt_ra);
	B_to_A(stack, cnt_rb);
	B_to_A(stack, cnt_pb - cnt_rb);
}

void B_to_A(t_total *stack, int size)
{
	int pivot_1;
	int pivot_2;
	int cnt_rb;
	int cnt_pa;
	int cnt_ra;
	
	int val;
	cnt_rb = 0;
	cnt_pa = 0;
	cnt_ra = 0;
	if (size == 1)
		return (pa(stack));
	if (size == 2)
	{
		if (stack->b.top->val < stack->b.top->next->val)
			sb(stack);
		pa(stack);
		pa(stack);
		return ;
	}
	if (size == 3)
	{
		int max = find_max(stack, 3, DESCEND);
		int min = find_min(stack, 3, DESCEND);

		int one = stack->b.top->val;
		int two = stack->b.top->next->val;
		int three = stack->b.top->next->next->val;

		if (min == one && max == three)
		{
			sb(stack);
			rb(stack);
			rb(stack);
			pa(stack);
			rrb(stack);
			rrb(stack);
			pa(stack);
			pa(stack);
		}
		else if (min == one && max == two)
		{
			rb(stack);
			pa(stack);
			pa(stack);
			rrb(stack);
			pa(stack);
		}		
		else if (min == two && max == three)
		{
			rb(stack);
			rb(stack);
			pa(stack);
			rrb(stack);
			rrb(stack);
			pa(stack);
			pa(stack);
		}		
		else if (min == three && max == two)
		{
			sb(stack);
			pa(stack);
			pa(stack);
			pa(stack);
		}
		else if (min == two && max == one)
		{
			pa(stack);
			sb(stack);
			pa(stack);
			pa(stack);
		}
		else
		{
			pa(stack);
			pa(stack);
			pa(stack);
		}
		return;
	}
	if (is_sorted(stack, size, DESCEND))
		return ;	
	set_pivot(stack->b, size, &pivot_1, &pivot_2, DESCEND);
	for (int i = 0; i < size ; i++)
	{
		val = stack->b.top->val;
		if (val <= pivot_2)
		{
			rb(stack);
			cnt_rb++;
		}
		else
		{
			pa(stack);
			cnt_pa++;
			if (val < pivot_1)
			{
				ra(stack);
				cnt_ra++;
			}
		}
	}
	A_to_B(stack, cnt_pa - cnt_ra);

	int j = 0;
	while (j < cnt_rb || j < cnt_ra)
	{
		if (j < cnt_rb && j < cnt_ra)
			rrr(stack);
		else if (j < cnt_rb)
			rrb(stack);
		else
			rra(stack);
		j++;
	}
	A_to_B(stack, cnt_ra);
	B_to_A(stack, cnt_rb);
}
