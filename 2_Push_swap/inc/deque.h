 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:35:56 by daeha             #+#    #+#             */
/*   Updated: 2024/03/30 23:34:23 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_H
# define DEQUE_H

#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>

/*
sa	|	node_swap(&a);
sb 	|	node_swap(&b);
ss 	|	node_swap(&a) && node_swap(&b)
pa 	|	push(&a, pop(&b, TOP), TOP);
pb 	|	push(&b, pop(&a, TOP), TOP);
ra 	|	push(&a, pop(&a, TOP), BOT);
rb 	|	push(&b, pop(&b, TOP), BOT);
rr 	|	ra && rb
rra |	push(&a, pop(&a, BOT), TOP);
rrb |	push(&b, pop(&b, BOT), TOP);
rrr |	rra && rrb
*/

typedef enum position
{
	TOP = 0,
	BOT = 1
} e_pos;

typedef struct s_node
{
	int		val;
	struct s_node *prev;
	struct s_node *next;
}	t_node;

typedef struct s_stack
{
	size_t size;
	t_node *top;
	t_node *bot;
}	t_stack;

typedef struct s_total
{
	size_t	size;
	t_stack	a;
	t_stack b;
}	t_total;

void	push(t_stack *stack, t_node *node, e_pos pos);
t_node	*pop(t_stack *stack, e_pos pos);
void 	node_swap(t_stack *stack);

#endif
