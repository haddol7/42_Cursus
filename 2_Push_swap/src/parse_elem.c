/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 18:17:10 by daeha             #+#    #+#             */
/*   Updated: 2024/04/17 20:42:47 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"
#include "ps_utils.h"

static char	*move_to_num(char *str, int *sign, int *is_digit_exists);
static int	atoi_fit(char **str, int *digit_in_argv);

void	parse_value(int argc, char **argv, t_total *stack)
{
	t_node	*node;
	int		cnt;
	int		result;
	int		is_digit_exists;

	cnt = 1;
	while (cnt < argc)
	{
		result = atoi_fit(&argv[cnt], &is_digit_exists);
		node = (t_node *)malloc(sizeof(t_node));
		if (node == NULL)
			exit(1);
		node->val = result;
		push(&stack->a, node, BOT);
		if (argv[cnt][0] == '\0')
		{
			is_digit_exists = 0;
			cnt++;
		}
	}
	stack->size = stack->a.size;
}

void	check_elem_dup(t_stack *a)
{
	size_t	i;
	size_t	j;
	t_node	*temp;
	t_node	*temp_j;

	i = 0;
	temp = a->top;
	while (i < a->size && a->size > 1)
	{
		j = 1;
		temp_j = temp->next;
		while (j < a->size)
		{
			if (temp->val == temp_j->val)
				ps_terminate();
			temp_j = temp_j->next;
			j++;
		}
		temp = temp->next;
		i++;
	}
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
			ps_terminate();
		(*str)++;
	}
	return ((int)(sign * result));
}

static char	*move_to_num(char *str, int *sign, int *is_digit_exists)
{
	while (*str == ' ')
		str++;
	if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (!*is_digit_exists && *str == '\0')
		ps_terminate();
	if (ft_isdigit(*str) == 0)
		ps_terminate();
	return (str);
}
