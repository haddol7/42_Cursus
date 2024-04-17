/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_case_b_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 00:14:32 by daeha             #+#    #+#             */
/*   Updated: 2024/04/18 01:49:49 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "control_elem.h"
#include "deque.h"

void	base_case_b_231(t_total *stack)
{
	sb(stack);
	pa(stack);
	pa(stack);
	pa(stack);
}

void	base_case_b_312(t_total *stack)
{
	pa(stack);
	sb(stack);
	pa(stack);
	pa(stack);
}

void	base_case_b_321(t_total *stack)
{
	pa(stack);
	pa(stack);
	pa(stack);
}
