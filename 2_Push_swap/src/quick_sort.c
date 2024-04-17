/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:56:31 by daeha             #+#    #+#             */
/*   Updated: 2024/04/17 23:58:16 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"
#include "control_elem.h"
#include "command.h"
#include "ps_utils.h"

static void	a_to_b(t_total *stack, int size);
static void	b_to_a(t_total *stack, int size);

void	quick_sort(t_total *stack, int size)
{
	t_count	cnt;
	int		pivot[2];

	ft_memset(&cnt, 0, sizeof(t_count));
	if (ps_is_stack_sorted(stack, size, ASCEND))
		return ;
	if (size <= 3)
		return (base_case_a(stack, size));
	set_pivot(stack->a, size, pivot, ASCEND);
	split_a_to_b(stack, size, pivot, &cnt);
	A_to_B(stack, cnt.ra);
	B_to_A(stack, cnt.p - cnt.rb);
	B_to_A(stack, cnt.rb);
}

void	set_pivot(t_stack stack, int size, int *pivot, e_order order)
{
	int		*ary;

	ary = malloc(sizeof(int) * size);
	if (ary == NULL)
		exit(1);
	ps_copy_array(ary, stack.top, size);
	ps_quick_sort(ary, 0, size - 1);
	if (order == ASCEND)
	{
		pivot[FIRST] = ary[(size - 1) - (size / 3) * 2];
		pivot[SECOND] = ary[(size - 1) - (size / 3 - 1)];
	}
	else
	{
		pivot[FIRST] = ary[size / 3 - 1];
		pivot[SECOND] = ary[(size / 3) * 2];
	}
	free(ary);
}

void	split_a_to_b(t_total *stack, int size, int *pivot, t_count *cnt)
{
	int		i;
	int		val;

	i = 0;
	while (i < size)
	{
		val = stack->a.top->val;
		if (val >= pivot[SECOND])
			ps_count_command(stack, ra, &cnt->ra);
		else
		{
			ps_count_command(stack, pb, &cnt->p);
			if (val <= pivot[FIRST])
				ps_count_command(stack, rb, &cnt->rb);
		}
		i++;
	}
}

void	rewind_a_to_b(t_total *stack, t_count cnt)
{
	int	j;
	
	j = 0;
	while (j < cnt.rb || j < cnt.ra)
	{
		if (j < cnt.rb && j < cnt.ra)
			rrr(stack);
		else if (j < cnt.rb)
			rrb(stack);
		else
			rra(stack);
		j++;
	}
}

static void	a_to_b(t_total *stack, int size)
{
	t_count	cnt;
	int		pivot[2];

	ft_memset(&cnt, 0, sizeof(t_count));
	if (ps_is_stack_sorted(stack, size, ASCEND))
		return ;
	if (size <= 3)
		return (base_case_a(stack, size));
	set_pivot(stack->a, size, pivot, ASCEND);
	split_a_to_b(stack, size, pivot, &cnt);
	rewind_a_to_b(stack, cnt);
	A_to_B(stack, cnt.ra);
	B_to_A(stack, cnt.rb);
	B_to_A(stack, cnt.p - cnt.rb);
}

static void b_to_a(t_total *stack, int size)
{
	int		pivot[2];
	t_count	cnt;

	ft_memset(&cnt, 0, sizeof(t_count));
	if (ps_is_stack_sorted(stack, size, DESCEND))
		return ;

	if (ps_is_stack_sorted(stack, size, DESCEND))
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

/*
static void b_to_a(t_total *stack, int size)
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
		int max = ps_find_max(stack, 3, DESCEND);
		int min = ps_find_min(stack, 3, DESCEND);

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
	if (ps_is_stack_sorted(stack, size, DESCEND))
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
*/
