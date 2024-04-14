/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:55:57 by daeha             #+#    #+#             */
/*   Updated: 2024/04/14 20:49:48 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control_elem.h"
#include "deque.h"
#include "command.h"

#include <unistd.h>

void B_to_A(t_total *stack, int size);
void A_to_B(t_total *stack, int size);

void swap_int(int *a, int *b)
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void print_stack(t_total *stack)
{
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
}

int find_pivot(t_stack stack, int size)
{
	int		*ary;
	int		pivot;
	t_node	*temp;

	ary = malloc(sizeof(int) * size);
	temp = stack.top;

	if (size == 1)
		return (stack.top->val);
	if (size == 2)
	{
//		ft_printf("!%d\n", stack.top->val);
//		ft_printf("!%d\n", stack.top->next->val);
		
		return (stack.top->val > stack.top->next->val ? stack.top->next->val : stack.top->val);
	}

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
	pivot = ary[size / 2];
	free(ary);
//	sleep(5);
	return (pivot);
}

void A_to_B(t_total *stack, int size)
{
	int pivot;
	int ra_cnt;
	int pb_cnt;

	ra_cnt = 0;
	pb_cnt = 0;
	if (size == 1)
		return;
	
//	print_stack(stack);
	pivot = find_pivot(stack->a, size);
//	ft_printf("pivot : %d\n", pivot);
	for (int i = 0; i < size; i++)
	{
		if (stack->a.top->val > pivot)
		{
			ra(stack);
			ra_cnt++;
		}
		else
		{
			pb(stack);
			pb_cnt++;
		}
	}
	for (int i = 0; i < ra_cnt; i++)
		rra(stack);
	A_to_B(stack, ra_cnt);
	B_to_A(stack, pb_cnt);
}

void B_to_A(t_total *stack, int size)
{
	int pivot;
	int rb_cnt;
	int pa_cnt;

	rb_cnt = 0;
	pa_cnt = 0;
	if (size == 1)
	{
		pa(stack);
		return ;
	}
//	print_stack(stack);
	pivot = find_pivot(stack->b, size);
//	ft_printf("pivot : %d\n", pivot);
	for (int i = 0; i < size; i++)
	{
		if (stack->b.top->val <= pivot)
		{
			rb(stack);
			rb_cnt++;
		}
		else
		{
			pa(stack);
			pa_cnt++;
		}
	}
	for (int i = 0; i < rb_cnt ; i++)
		rrb(stack);
	A_to_B(stack, pa_cnt);
	B_to_A(stack, rb_cnt);
}


int main(int argc, char **argv)
{
	t_total stack;
	
	if (argc <= 1)
		return (1);
	ft_memset(&stack, 0, sizeof(t_total));
	stack.size = parse_value(argc, argv, &stack.a);
	check_elem_dup(stack.a);
	A_to_B(&stack, stack.size);
//	print_stack(&stack);
}
