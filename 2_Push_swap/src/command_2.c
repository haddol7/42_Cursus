/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:57:01 by daeha             #+#    #+#             */
/*   Updated: 2024/04/12 19:22:00 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void ra(t_total *stack)
{
	push(&stack->a, pop(&stack->a, TOP), BOT);
	ft_printf("ra\n");
}

void rb(t_total *stack)
{
	push(&stack->b, pop(&stack->b, TOP), BOT);
	ft_printf("rb\n");
}

void rr(t_total *stack)
{
	push(&stack->a, pop(&stack->a, TOP), BOT);
	push(&stack->b, pop(&stack->b, TOP), BOT);
	ft_printf("rr\n");
}

void rra(t_total *stack)
{
	push(&stack->a, pop(&stack->a, BOT), TOP);
	ft_printf("rra\n");
}

void rrb(t_total *stack)
{
	push(&stack->b, pop(&stack->b, BOT), TOP);
	ft_printf("rrb\n");
}
