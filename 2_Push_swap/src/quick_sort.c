/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:56:31 by daeha             #+#    #+#             */
/*   Updated: 2024/04/18 00:45:10 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"
#include "control_elem.h"
#include "command.h"
#include "ps_utils.h"

static void	set_pivot(t_stack stack, int size, int *pivot, t_order order);
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
	a_to_b(stack, cnt.ra);
	b_to_a(stack, cnt.p - cnt.rb);
	b_to_a(stack, cnt.rb);
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
	a_to_b(stack, cnt.ra);
	b_to_a(stack, cnt.rb);
	b_to_a(stack, cnt.p - cnt.rb);
}

static void	b_to_a(t_total *stack, int size)
{
	int		pivot[2];
	t_count	cnt;

	ft_memset(&cnt, 0, sizeof(t_count));
	if (ps_is_stack_sorted(stack, size, DESCEND))
		return ;
	if (size <= 3)
		return (base_case_b(stack, size));
	set_pivot(stack->b, size, pivot, DESCEND);
	split_b_to_a(stack, size, pivot, &cnt);
	a_to_b(stack, cnt.p - cnt.ra);
	rewind_b_to_a(stack, cnt);
	a_to_b(stack, cnt.ra);
	b_to_a(stack, cnt.rb);
}

static void	set_pivot(t_stack stack, int size, int *pivot, t_order order)
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
