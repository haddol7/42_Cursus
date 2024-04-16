/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:55:57 by daeha             #+#    #+#             */
/*   Updated: 2024/04/16 22:07:41 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "control_elem.h"
#include "deque.h"
#include "command.h"


void leak(void)
{
	system("leaks push_swap");
}

int main(int argc, char **argv)
{
	t_total stack;
	
	if (argc < 2)
		return (1);
	ft_memset(&stack, 0, sizeof(t_total));
	parse_value(argc, argv, &stack);
	check_elem_dup(&stack.a);
	if (stack.size <= 5)
		small_sort(&stack, stack.size);
	else
		quick_sort(&stack, stack.size);
	while (stack.a.size)
		free(pop(&stack.a, TOP));
	atexit(leak);
	return (0);
}
