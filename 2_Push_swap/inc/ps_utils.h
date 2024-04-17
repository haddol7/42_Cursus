/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:34:45 by daeha             #+#    #+#             */
/*   Updated: 2024/04/17 21:20:16 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_UTILS_H
# define PS_UTILS_H

void	ps_terminate(void);
void	ps_swap(int *a, int *b);
void	ps_copy_array(int *ary, t_node *node, int size);
void	ps_quick_sort(int *ary, int left, int right);

int		ps_find_max(t_total *stack, int size, e_order order);
int		ps_find_min(t_total *stack, int size, e_order order);

#endif
