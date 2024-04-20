/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:32:07 by daeha             #+#    #+#             */
/*   Updated: 2024/04/21 00:51:19 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"
#include "control_elem.h"
#include "command.h"
#include "ps_utils.h"

void	split_init(t_total *stack, int size, int *pivot, t_count *cnt)
{
	int	i;
	int	val;

	i = 0;
	while (i < size)
	{
		val = stack->a.top->val;
		if (val >= pivot[SECOND])
			ps_count_command(stack, ra, &cnt->ra);
		else
		{
			ps_count_command(stack, pb, &cnt->p);
			if (val <= pivot[FIRST])
				ps_count_command(stack, rb, &cnt->rb);
		}
		i++;
	}
}

void	split_a_to_b(t_total *stack, int size, int *pivot, t_count *cnt)
{
	int	i;
	int	val;

	i = 0;
	while (i < size)
	{
		val = stack->a.top->val;
		if (val >= pivot[SECOND])
			ps_count_command(stack, ra, &cnt->ra);
		else
		{
			ps_count_command(stack, pb, &cnt->p);
			if (val > pivot[FIRST])
				ps_count_command(stack, rb, &cnt->rb);
		}
		i++;
	}
}

void	split_b_to_a(t_total *stack, int size, int *pivot, t_count *cnt)
{
	int	i;
	int	val;

	i = 0;
	while (i < size)
	{
		val = stack->b.top->val;
		if (val <= pivot[FIRST])
			ps_count_command(stack, rb, &cnt->rb);
		else
		{
			ps_count_command(stack, pa, &cnt->p);
			if (val < pivot[SECOND])
				ps_count_command(stack, ra, &cnt->ra);
		}
		i++;
	}
}

void	rewind_a_to_b(t_total *stack, t_count cnt)
{
	int	j;

	j = 0;
	while (j < cnt.rb || j < cnt.ra)
	{
		if (j < cnt.rb && j < cnt.ra)
			rrr(stack);
		else if (j < cnt.rb)
			rrb(stack);
		else
			rra(stack);
		j++;
	}
}

void	rewind_b_to_a(t_total *stack, t_count cnt)
{
	int	j;

	j = 0;
	while (j < cnt.rb || j < cnt.ra)
	{
		if (j < cnt.rb && j < cnt.ra)
			rrr(stack);
		else if (j < cnt.rb)
			rrb(stack);
		else
			rra(stack);
		j++;
	}
}
