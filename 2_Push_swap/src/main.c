/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:55:57 by daeha             #+#    #+#             */
/*   Updated: 2024/03/30 23:14:54 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"
#include "../inc/deque.h"

void print_top(t_stack a)
{
	t_node *cur = a.top;
	printf("========\n");
	for (int i = 0; i < a.size; i++)
	{
		printf("%d\n",cur->val);
		cur = cur->next;
	}
	printf("========\n");
}

int main(int argc, char **argv)
{
	t_stack a;
	t_stack b;

	a.size = 0;
	b.size = 0;

	t_node	node1;
	t_node	node2;
	t_node	node3;
	t_node	node4;

	node1.val = 1;
	node2.val = 2;
	node3.val = 3;
	node4.val = 4;

	push(&a, &node1, TOP);
	push(&a, &node2, TOP);
	push(&a, &node3, TOP);
	push(&a, &node4, TOP);
	
	print_top(a);
	
	push(&b, pop(&a, TOP), TOP);
	push(&b, pop(&a, TOP), TOP);
	push(&b, pop(&a, TOP), TOP);
	print_top(a);
	print_top(b);

	ft_printf("test");

}
