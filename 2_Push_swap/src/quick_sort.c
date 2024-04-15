/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:56:31 by daeha             #+#    #+#             */
/*   Updated: 2024/04/15 20:42:08 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control_elem.h"
#include "command.h"
#include "deque.h"

void swap_int(int *a, int *b)
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}


void	set_pivot(t_stack stack, int size, int *pivot_1, int *pivot_2)
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

	*pivot_2 = ary[(size / 3) - 1];
	*pivot_1 = ary[size - (size / 3)];
	ft_printf("pivot_1 : %d \npivot_2 : %d\n", *pivot_1, *pivot_2);
	free(ary);
//	sleep(5);
}

static void B_to_A(t_total *stack, int size);

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
	set_pivot(stack->a, size, &pivot_1, &pivot_2);
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
	
	//the size of chunk 1 and chunk 3 is equivalant
	for (int i = 0; i < cnt_rb; i++)
		rrr(stack);

	
	t_node *temp;

	ft_printf("stack A : ");
	temp = stack->a.top;
	for (int i = 0; i < stack->a.size; i++)
	{
		ft_printf("%d ", temp->val);
		temp = temp->next;
	}
	ft_printf("\nstack B : ");
	temp = stack->b.top;
	for (int i = 0; i < stack->b.size; i++)
	{
		ft_printf("%d ", temp->val);
		temp = temp->next;
	}
	ft_printf("\n");

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
		
	set_pivot(stack->b, size, &pivot_1, &pivot_2);
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

	t_node *temp;

	ft_printf("stack A : ");
	temp = stack->a.top;
	for (int i = 0; i < stack->a.size; i++)
	{
		ft_printf("%d ", temp->val);
		temp = temp->next;
	}
	ft_printf("\nstack B : ");
	temp = stack->b.top;
	for (int i = 0; i < stack->b.size; i++)
	{
		ft_printf("%d ", temp->val);
		temp = temp->next;
	}
	ft_printf("\n");


	//chunk 1 must be sorted before reverse
	A_to_B(stack, cnt_ra);
	
	//the size of chunk 1 and chunk 3 is equivalant
	for (int i = 0; i < cnt_rb; i++)
		rrr(stack);
	
	A_to_B(stack, cnt_pa - cnt_ra);
	B_to_A(stack, cnt_rb);
}
