/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:17:10 by daeha             #+#    #+#             */
/*   Updated: 2024/04/01 18:21:32 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

size_t	put_value_in_stack_a(int argc, char **argv, t_stack *a)
{
	t_node	*node;
	int		cnt;
	int		result;
	int		is_digit_exists;

	cnt = 1;
	while (cnt < argc)
	{
		result = atoi_fit(&argv[cnt], &is_digit_exists);
		if (is_digit_exists == 1)
		{
			node = (t_node *)malloc(sizeof(t_node));
			if (node == NULL)
				exit(1);
			node->val = result;
			push(a, node, BOT);
		}
		if (argv[cnt][0] == '\0')
			cnt++;
	}
	return (a->size);
}

static char	*move_to_num(char *str, int *sign, int *is_digit_exists)
{
	*is_digit_exists = 0;
	if (*str == ' ')
		str++;
	if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (ft_isdigit(*str))
		*is_digit_exists = 1;
	else
		terminate();
	return (str);
}

static int	atoi_fit(char **str, int *is_digit_exists)
{
	long	result;
	int		temp;
	int		sign;

	sign = 1;
	result = 0;
	*str = move_to_num(*str, &sign, is_digit_exists);
	while (**str >= '0' && **str <= '9')
	{
		result *= 10;
		result += **str - '0';
		temp = (int)result;
		if (temp != result)
			terminate();
		(*str)++;
	}
	return ((int)(sign * result));
}

void check_elem_dup(t_stack a)
{
	size_t	i;
	size_t	j;
	t_node	*temp;
	t_node	*temp_j;
	
	i = 0;
	temp = a.top;
	while (i < a.size && a.size > 1)
	{
		j = 1;
		temp_j = temp->next;
		while (j < a.size)
		{
			if (temp->val == temp_j->val)
				terminate();
			temp_j = temp_j->next;
			j++;
		}
		temp = temp->next;
		i++;
	}
}

static int		command_to_stack_sub(t_total *stack, char *command)
{
	if (!ft_strncmp("rr\n", command, 3))
	{
		push(&stack->a, pop(&stack->a, TOP), BOT);
		push(&stack->b, pop(&stack->b, TOP), BOT);
	}
	else if (!ft_strncmp("rra\n", command, 3))
		push(&stack->a, pop(&stack->a, BOT), TOP);
	else if (!ft_strncmp("rrb\n", command, 3))
		push(&stack->b, pop(&stack->b, BOT), TOP);
	else if (!ft_strncmp("rrr\n", command, 3))
	{
		push(&stack->a, pop(&stack->a, BOT), TOP);
		push(&stack->b, pop(&stack->b, BOT), TOP);
	}
	else
		terminate();
	return (0);
}

int		command_to_stack(t_total *stack, char *command)
{
	if (command == NULL)
		return (1);
	if (!ft_strncmp("sa\n", command, 3))
		node_swap(&stack->a);
	else if (!ft_strncmp("sb\n", command, 3))
		node_swap(&stack->b);
	else if (!ft_strncmp("ss\n", command, 3))
	{
		node_swap(&stack->a);
		node_swap(&stack->b);
	}
	else if (!ft_strncmp("pa\n", command, 3))
		push(&stack->a, pop(&stack->b, TOP), TOP);
	else if (!ft_strncmp("pb\n", command, 3))
		push(&stack->b, pop(&stack->a, TOP), TOP);
	else if (!ft_strncmp("ra\n", command, 3))
		push(&stack->a, pop(&stack->a, TOP), BOT);
	else if (!ft_strncmp("rb\n", command, 3))
		push(&stack->b, pop(&stack->b, TOP), BOT);
	else	
		return (command_to_stack_sub(stack, command));
	return (0);
}
