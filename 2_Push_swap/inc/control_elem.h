/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_elem.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:27:50 by daeha             #+#    #+#             */
/*   Updated: 2024/04/18 02:10:31 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_ELEM_H
# define CONTROL_ELEM_H

# include "deque.h"
# define FIRST 0
# define SECOND 1
# define THIRD 2

typedef struct s_count
{
	int	ra;
	int	p;
	int	rb;
}	t_count;

//parse_elem.c
size_t	parse_value(int argc, char **argv, t_total *stack);
void	check_elem_dup(t_stack *a);

//quick_sort.c
void	quick_sort(t_total *stack, int size);

//quick_sort_split.c
void	split_init(t_total *stack, int size, int *pivot, t_count *cnt);
void	split_a_to_b(t_total *stack, int size, int *pivot, t_count *cnt);
void	split_b_to_a(t_total *stack, int size, int *pivot, t_count *cnt);
void	rewind_a_to_b(t_total *stack, t_count cnt);
void	rewind_b_to_a(t_total *stack, t_count cnt);

//base_case_a.c
void	base_case_a(t_total *stack, int size);

//base_case_b_1.c
void	base_case_b(t_total *stack, int size);

//base_case_b_2.c
void	base_case_b_231(t_total *stack);
void	base_case_b_312(t_total *stack);
void	base_case_b_321(t_total *stack);

//small_sort.c
void	small_sort(t_total *stack, int size);
#endif
