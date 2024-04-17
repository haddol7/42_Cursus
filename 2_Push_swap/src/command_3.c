/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:57:09 by daeha             #+#    #+#             */
/*   Updated: 2024/04/17 20:33:13 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	rrr(t_total *stack)
{
	push(&stack->a, pop(&stack->a, BOT), TOP);
	push(&stack->b, pop(&stack->b, BOT), TOP);
	ft_printf("rrr\n");
}
