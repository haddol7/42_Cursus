/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_elem.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:27:50 by daeha             #+#    #+#             */
/*   Updated: 2024/04/17 22:07:05 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_ELEM_H
# define CONTROL_ELEM_H

#include "deque.h"

int		command_to_stack(t_total *stack, char *command);

//parse_elem.c
size_t	parse_value(int argc, char **argv, t_total *stack);
void 	check_elem_dup(t_stack *a);

void quick_sort(t_total *stack, int size);
void small_sort(t_total *stack, int size);
#endif
