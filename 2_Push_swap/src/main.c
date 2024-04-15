/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:55:57 by daeha             #+#    #+#             */
/*   Updated: 2024/04/15 20:52:26 by daeha            ###   ########.fr       */
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

int main(int argc, char **argv)
{
	t_total stack;
	
	if (argc <= 1)
		return (1);
	ft_memset(&stack, 0, sizeof(t_total));
	stack.size = parse_value(argc, argv, &stack.a);
	check_elem_dup(stack.a);
	
	// for (int i = 0; i < stack.size ; i++)
	// {
	// 	pb(&stack);
	// 	rb(&stack);
	// }
//	print_stack(&stack);
//	sort_small_sort(&stack, stack.size, ASCEND);
	A_to_B(&stack, stack.size);
//	print_stack(&stack);
}
