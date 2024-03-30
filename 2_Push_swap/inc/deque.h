/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:35:56 by daeha             #+#    #+#             */
/*   Updated: 2024/03/30 19:29:56 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

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
