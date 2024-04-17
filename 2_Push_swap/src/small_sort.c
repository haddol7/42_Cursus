/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:05:19 by daeha             #+#    #+#             */
/*   Updated: 2024/04/17 21:13:31 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "control_elem.h"
#include "command.h"
#include "ps_utils.h"

static void	sort_3(t_total *stack);
static void	sort_4(t_total *stack);
static void	sort_5(t_total *stack);
static void	get_min_values(t_stack stack, int *min_1, int *min_2);


void	small_sort(t_total *stack, int size)
{
	if (size == 1)
		return ;
	else if (size == 2)
	{
		if (stack->a.top->val > stack->a.top->next->val)
			sa(stack);
	}
	else if (size == 3)
		sort_3(stack);
	else if (size == 4)
		sort_4(stack);
	else
		sort_5(stack);
}

static void	sort_3(t_total *stack)
{
	int	max;

	max = find_max(stack, 3);
	if (max == stack->a.top->val)
		ra(stack);
	else if (max == stack->a.top->next->val)
		rra(stack);
	if (stack->a.top->val > stack->a.top->next->val)
		sa(stack);
}

static void	sort_4(t_total *stack)
{
	int	cnt;
	int	max;

	max = find_max(stack, 4);
	while (stack->a.top->val != max)
		rra(stack);
	pb(stack);
	sort_3(stack);
	pa(stack);
	ra(stack);
}

static void	sort_5(t_total *stack)
{
	int	cnt;
	int	min1;
	int	min2;

	cnt = 0;
	get_min_values(stack->a, &min1, &min2);
	while (cnt < 2)
	{
		if (stack->a.top->val == min1 || stack->a.top->val == min2)
		{
			pb(stack);
			cnt++;
		}
		rra(stack);
	}
	sort_3(stack);
	if (stack->b.top->val < stack->b.bot->val)
		sb(stack);
	pa(stack);
	pa(stack);
}

static void	get_min_values(t_stack stack, int *min_1, int *min_2)
{
	int		ary[5];
	t_node	*temp;

	ps_copy_array(ary, stack.top, 5);
	ps_quick_sort(ary, 0, 4);
	*min_1 = ary[0];
	*min_2 = ary[1];
}
