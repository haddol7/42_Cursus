/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:25:51 by daeha             #+#    #+#             */
/*   Updated: 2024/04/17 20:37:57 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"
#include "utils.h"

static int		command_to_stack_sub(t_total *stack, char *command);

int	command_to_stack(t_total *stack, char *command)
{
	if (command == NULL)
		return (1);
	if (!ft_strncmp("sa\n", command, 3))
		node_swap(&stack->a);
	else if (!ft_strncmp("sb\n", command, 3))
		node_swap(&stack->b);
	else if (!ft_strncmp("ss\n", command, 3))
	{
		node_swap(&stack->a);
		node_swap(&stack->b);
	}
	else if (!ft_strncmp("pa\n", command, 3))
		push(&stack->a, pop(&stack->b, TOP), TOP);
	else if (!ft_strncmp("pb\n", command, 3))
		push(&stack->b, pop(&stack->a, TOP), TOP);
	else if (!ft_strncmp("ra\n", command, 3))
		push(&stack->a, pop(&stack->a, TOP), BOT);
	else if (!ft_strncmp("rb\n", command, 3))
		push(&stack->b, pop(&stack->b, TOP), BOT);
	else
		return (command_to_stack_sub(stack, command));
	return (0);
}

static int	command_to_stack_sub(t_total *stack, char *command)
{
	if (!ft_strncmp("rr\n", command, 3))
	{
		push(&stack->a, pop(&stack->a, TOP), BOT);
		push(&stack->b, pop(&stack->b, TOP), BOT);
	}
	else if (!ft_strncmp("rra\n", command, 3))
		push(&stack->a, pop(&stack->a, BOT), TOP);
	else if (!ft_strncmp("rrb\n", command, 3))
		push(&stack->b, pop(&stack->b, BOT), TOP);
	else if (!ft_strncmp("rrr\n", command, 3))
	{
		push(&stack->a, pop(&stack->a, BOT), TOP);
		push(&stack->b, pop(&stack->b, BOT), TOP);
	}
	else
		ps_terminate();
	return (0);
}
