/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_case_b_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:58:22 by daeha             #+#    #+#             */
/*   Updated: 2024/04/18 21:32:53 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_utils.h"
#include "command.h"
#include "control_elem.h"
#include "deque.h"

static void	base_case_b_under_two(t_total *stack, int size);
static void	base_case_b_123(t_total *stack);
static void	base_case_b_132(t_total *stack);
static void	base_case_b_213(t_total *stack);

void	base_case_b(t_total *stack, int size)
{
	int	max;
	int	min;
	int	val[3];

	if (size <= 2)
		return (base_case_b_under_two(stack, size));
	val[FIRST] = stack->b.top->val;
	val[SECOND] = stack->b.top->next->val;
	max = ps_find_max(stack, 3, DESCEND);
	min = ps_find_min(stack, 3, DESCEND);
	val[THIRD] = stack->b.top->next->next->val;
	if (min == val[FIRST] && max == val[THIRD])
		base_case_b_123(stack);
	else if (min == val[FIRST] && max == val[SECOND])
		base_case_b_132(stack);
	else if (min == val[SECOND] && max == val[THIRD])
		base_case_b_213(stack);
	else if (min == val[THIRD] && max == val[SECOND])
		base_case_b_231(stack);
	else if (min == val[SECOND] && max == val[FIRST])
		base_case_b_312(stack);
	else
		base_case_b_321(stack);
}

static void	base_case_b_under_two(t_total *stack, int size)
{
	if (size == 1)
		pa(stack);
	else
	{
		if (stack->b.top->val < stack->b.top->next->val)
			sb(stack);
		pa(stack);
		pa(stack);
	}
}

static void	base_case_b_123(t_total *stack)
{
	pa(stack);
	ra(stack);
	pa(stack);
	pa(stack);
	sa(stack);
	rra(stack);
}

static void	base_case_b_132(t_total *stack)
{
	rb(stack);
	pa(stack);
	pa(stack);
	rrb(stack);
	pa(stack);
}

static void	base_case_b_213(t_total *stack)
{
	pa(stack);
	sb(stack);
	pa(stack);
	sa(stack);
	pa(stack);
}
