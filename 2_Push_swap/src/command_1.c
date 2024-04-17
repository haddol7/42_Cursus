/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:54:55 by daeha             #+#    #+#             */
/*   Updated: 2024/04/18 00:20:51 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	sa(t_total *stack)
{
	node_swap(&stack->a);
	ft_printf("sa\n");
}

void	sb(t_total *stack)
{
	node_swap(&stack->b);
	ft_printf("sb\n");
}

void	ss(t_total *stack)
{
	node_swap(&stack->a);
	node_swap(&stack->b);
	ft_printf("ss\n");
}

void	pa(t_total *stack)
{
	push(&stack->a, pop(&stack->b, TOP), TOP);
	ft_printf("pa\n");
}

void	pb(t_total *stack)
{
	push(&stack->b, pop(&stack->a, TOP), TOP);
	ft_printf("pb\n");
}
