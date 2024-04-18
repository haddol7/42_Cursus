/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 21:55:57 by daeha             #+#    #+#             */
/*   Updated: 2024/04/18 17:03:23 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control_elem.h"
#include "deque.h"

int	main(int argc, char **argv)
{
	t_total	stack;

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
	return (0);
}
