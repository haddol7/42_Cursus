/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:23:00 by daeha             #+#    #+#             */
/*   Updated: 2024/04/17 21:07:51 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "deque.h"
#include "ps_utils.h"

void	ps_terminate(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	ps_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ps_copy_array(int *ary, t_node *node, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ary[i] = node->val;
		node = node->next;
		i++;
	}
}

void	ps_quick_sort(int *ary, int left, int right)
{
	int	i;
	int	j;
	int	pivot;

	i = left;
	j = right;
	pivot = ary[left];
	while (i <= j)
	{
		while (ary[i] < pivot)
			i++;
		while (ary[j] > pivot)
			j--;
		if (i <= j)
		{
			ps_swap(ary + i, ary + j);
			i++;
			j--;
		}
	}
	if (left < j)
		ps_quick_sort(ary, left, j);
	if (i < right)
		ps_quick_sort(ary, i, right);
}
