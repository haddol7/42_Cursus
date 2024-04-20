/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:17:10 by daeha             #+#    #+#             */
/*   Updated: 2024/04/21 00:51:16 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "deque.h"
#include "ps_utils.h"

static char	*move_to_num(char *str, int *sign);
static int	atoi_fit(char **str);

void	parse_value(int argc, char **argv, t_total *stack)
{
	t_node	*node;
	int		cnt;
	int		result;

	cnt = 1;
	while (cnt < argc)
	{
		result = atoi_fit(&argv[cnt]);
		node = (t_node *)malloc(sizeof(t_node));
		if (node == NULL)
			exit(1);
		node->val = result;
		push(&stack->a, node, BOT);
		if (argv[cnt][0] == '\0')
			cnt++;
	}
	stack->size = stack->a.size;
}

void	check_elem_dup(t_stack *a)
{
	t_node	*temp;
	t_node	*temp_j;
	
	temp = a->top;
	while (temp != a->bot && a->size > 1)
	{
		temp_j = temp->next;
		while (1)
		{
			if (temp->val == temp_j->val)
				ps_terminate();
			if (temp_j == a->bot)
				break;
			temp_j = temp_j->next;
		}
		temp = temp->next;
	}
}

static int	atoi_fit(char **str)
{
	long	result;
	int		temp;
	int		sign;

	sign = 1;
	result = 0;
	*str = move_to_num(*str, &sign);
	while (**str >= '0' && **str <= '9')
	{
		result *= 10;
		result = result + (sign) * (**str - '0');
		temp = (int)result;
		if (temp != result)
			ps_terminate();
		(*str)++;
	}
	if (**str != ' ' && **str != '\0')
		ps_terminate();
	return ((int)(result));
}

static char	*move_to_num(char *str, int *sign)
{
	if (*str == ' ')
		str++;
	if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (!ft_isdigit(*str))
		ps_terminate();
	return (str);
}
