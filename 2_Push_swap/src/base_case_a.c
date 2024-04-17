/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_case_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:39:32 by daeha             #+#    #+#             */
/*   Updated: 2024/04/18 00:52:29 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_utils.h"
#include "command.h"
#include "control_elem.h"
#include "deque.h"

static void	base_case_a_132(t_total *stack);
static void	base_case_a_231(t_total *stack);
static void	base_case_a_312(t_total *stack);
static void	base_case_a_321(t_total *stack);

void	base_case_a(t_total *stack, int size)
{
	int	max;
	int	min;
	int	val[3];

	val[FIRST] = stack->a.top->val;
	val[SECOND] = stack->a.top->next->val;
	if (size <= 2)
	{
		if (size == 2 && val[FIRST] > val[SECOND])
			sa(stack);
		return ;
	}
	max = ps_find_max(stack, 3, ASCEND);
	min = ps_find_min(stack, 3, ASCEND);
	val[THIRD] = stack->a.top->next->next->val;
	if (min == val[FIRST] && max == val[SECOND])
		base_case_a_132(stack);
	else if (min == val[SECOND] && max == val[THIRD])
		sa(stack);
	else if (min == val[THIRD] && max == val[SECOND])
		base_case_a_231(stack);
	else if (min == val[SECOND] && max == val[FIRST])
		base_case_a_312(stack);
	else if (min == val[THIRD] && max == val[FIRST])
		base_case_a_321(stack);
}

static void	base_case_a_132(t_total *stack)
{
	pb(stack);
	sa(stack);
	pa(stack);
}

static void	base_case_a_231(t_total *stack)
{
	ra(stack);
	ra(stack);
	pb(stack);
	rra(stack);
	rra(stack);
	pa(stack);
}

static void	base_case_a_312(t_total *stack)
{
	sa(stack);
	pb(stack);
	sa(stack);
	pa(stack);
}

static void	base_case_a_321(t_total *stack)
{
	sa(stack);
	ra(stack);
	ra(stack);
	pb(stack);
	rra(stack);
	rra(stack);
	pa(stack);
}
