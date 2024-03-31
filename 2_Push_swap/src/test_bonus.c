/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:02:49 by daeha             #+#    #+#             */
/*   Updated: 2024/03/31 15:35:08 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/deque.h"

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

#include <stdio.h>

int main()
{
	printf("test");
}
