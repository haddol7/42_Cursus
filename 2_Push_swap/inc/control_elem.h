/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_elem.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:27:50 by daeha             #+#    #+#             */
/*   Updated: 2024/04/01 18:32:27 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

//command.c
int		command_to_stack(t_total *stack, char *command);

//parse_elem.c
size_t	put_value_in_stack_a(int argc, char **argv, t_stack *a);
void 	check_elem_dup(t_stack a);
