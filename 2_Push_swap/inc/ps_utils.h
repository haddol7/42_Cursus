/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:34:45 by daeha             #+#    #+#             */
/*   Updated: 2024/04/18 00:53:39 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_UTILS_H
# define PS_UTILS_H

# include "deque.h"

//push_swap_utils_1.c
void	ps_terminate(void);
void	ps_swap(int *a, int *b);
void	ps_copy_array(int *ary, t_node *node, int size);
void	ps_quick_sort(int *ary, int left, int right);

//push_swap_utils_2.c
int		ps_find_max(t_total *stack, int size, t_order order);
int		ps_find_min(t_total *stack, int size, t_order order);
int		ps_is_stack_sorted(t_total *stack, int size, t_order sort);
int		ps_count_command(t_total *stack, void (*command)(t_total *), int *cnt);

#endif
