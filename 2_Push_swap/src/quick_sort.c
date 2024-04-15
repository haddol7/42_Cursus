/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:56:31 by daeha             #+#    #+#             */
/*   Updated: 2024/04/15 16:03:28 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "deque.h"

static void B_to_A(t_total *stack, int size);

void A_to_B(t_total *stack, int size)
{
	int pivot_1;
	int pivot_2;
	int cnt_ra;
	int cnt_pb;
	int cnt_rb;
	
	int val;
	
	if (size <= 5)
	{
		sort_small_case(stack, size, 1);
		return ;	
	}
	set_pivot(stack, size, &pivot_1, &pivot_2);
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
				cnt_rb;
			}
		}
	}
	
	//the size of chunk 1 and chunk 3 is equivalant
	for (int i = 0; i < cnt_rb; i++)
		rrr(stack);
	
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
	
	if (size <= 5)
	{
		sort_small_case(stack, size, 0);
		for (int i = 0; i < size; i++)
			pa(stack);
		return ;	
	}
	set_pivot(stack, size, &pivot_1, &pivot_2);
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
			if (val >= pivot_1)
			{
				ra(stack);
				cnt_ra;
			}
		}
	}
	
	//chunk 1 must be sorted before reverse
	A_to_B(stack, cnt_ra);
	
	//the size of chunk 1 and chunk 3 is equivalant
	for (int i = 0; i < cnt_rb; i++)
		rrr(stack);
	
	A_to_B(stack, cnt_pa - cnt_ra);
	B_to_A(stack, cnt_rb);
}
