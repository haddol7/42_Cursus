/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:45:43 by daeha             #+#    #+#             */
/*   Updated: 2024/04/18 16:06:10 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_H
# define DEQUE_H

# include <stddef.h>
# include "libft.h"

typedef enum e_position
{
	TOP = 0,
	BOT = 1
}	t_pos;

typedef enum e_order
{
	ASCEND = 0,
	DESCEND = 1
}	t_order;

typedef struct s_node
{
	int				val;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	size_t	size;
	t_node	*top;
	t_node	*bot;
}	t_stack;

typedef struct s_total
{
	size_t	size;
	t_stack	a;
	t_stack	b;
}	t_total;

void	push(t_stack *stack, t_node *node, t_pos pos);
t_node	*pop(t_stack *stack, t_pos pos);
void	node_swap(t_stack *stack);

#endif
