/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:55:57 by daeha             #+#    #+#             */
/*   Updated: 2024/04/16 16:51:15 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control_elem.h"
#include "deque.h"
#include "command.h"

#include <unistd.h>

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

static void	check_stack_sorted_free(t_total *stack)
{
	int		is_sorted;

	is_sorted = 1;
	if (stack->b.size != 0)
	{
		while (stack->b.size > 0)
			free(pop(&stack->b, BOT));
		is_sorted = 0;
	}
	while (stack->a.size > 0)
	{
		if (stack->a.size > 1 && stack->a.top->val > stack->a.top->next->val)
			is_sorted = 0;
		free(pop(&stack->a, TOP));
	}
	if (is_sorted == 0)
		ft_printf("KO\n");
	else
		ft_printf("OK\n");
}

int main(int argc, char **argv)
{
	t_total stack;
	
	if (argc <= 1)
		return (1);
	ft_memset(&stack, 0, sizeof(t_total));
	stack.size = parse_value(argc, argv, &stack.a);
	check_elem_dup(stack.a);
	if (stack.size <= 1)
		sort_small_sort(&stack, stack.size, ASCEND);
	else
		initial(&stack, stack.size);
//	print_stack(&stack);
//	check_stack_sorted_free(&stack);
}
