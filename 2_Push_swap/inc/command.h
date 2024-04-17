/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:21:29 by daeha             #+#    #+#             */
/*   Updated: 2024/04/18 00:35:48 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "deque.h"

//command_1.c
//command_2.c
//command_3.c
void	sa(t_total *stack);
void	sb(t_total *stack);
void	ss(t_total *stack);
void	pa(t_total *stack);
void	pb(t_total *stack);
void	ra(t_total *stack);
void	rb(t_total *stack);
void	rr(t_total *stack);
void	rra(t_total *stack);
void	rrb(t_total *stack);
void	rrr(t_total *stack);
//command_bonus.c
int		command_to_stack(t_total *stack, char *command);

#endif
