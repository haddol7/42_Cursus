/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:02:49 by daeha             #+#    #+#             */
/*   Updated: 2024/03/31 22:32:19 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

/*
sa	|	node_swap(&a);
sb 	|	node_swap(&b);
ss 	|	node_swap(&a) && node_swap(&b)
pa 	|	push(&a, pop(&b, TOP), TOP);
pb 	|	push(&b, pop(&a, TOP), TOP);
ra 	|	push(&a, pop(&a, TOP), BOT);
rb 	|	push(&b, pop(&b, TOP), BOT);
rr 	|	ra && rb
rra |	push(&a, pop(&a, BOT), TOP);
rrb |	push(&b, pop(&b, BOT), TOP);
rrr |	rra && rrb
*/

#include <stdio.h>
#include "ft_printf.h"
#include "libft.h"

void	leaks(void)
{
	system("leaks checker");
}

void	terminate(void)
{
	ft_printf("Error\n");
	exit(1);
}

static char	*move_to_num(char *str, int *sign, int *nothing)
{
	*nothing = 0;
	while (*str != '\0' && *str == ' ')
		str++;
	if (*str != '\0')
	{
		if (*str == '-' && *(str + 1))
		{
			*sign = -1;
			return (++str);
		}
		else if (*str == '+' && *(str + 1))
			return (++str);
		if (*str < '0' || *str > '9')
			terminate();
	}
	else
		*nothing = 1;
	return (str);
}

int	atoi_fit(char **str, int *nothing)
{
	long	result;
	int		temp;
	int		sign;

	sign = 1;
	result = 0;
	*str = move_to_num(*str, &sign, nothing);
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


// 1. argv 인자를 받고 이를 stack a에 저장한다.
// int main(int argc, char **argv)
// {
// 	t_total	stack;
// 	char	*command;
// 	int		is_eof;

// 	atexit(leaks);
// 	is_eof = 0;
// 	stack.size = put_value_in_stack_a(argc, argv, &stack.a);
//	validate_overlap();
// 	while (!is_eof)
// 	{
// 		command = get_next_line(0);
// 		is_eof = command_to_stack(&stack, command);
// 		free(command);
// 	}
// 	check_stack_sorted(stack);
// 	return (0);
// }

void	check_stack_sorted(t_total *stack)
{
	t_node	*temp;
	t_node 	*cur;
	int		is_sorted;
	int 	val;

	val = -2147483648;
	is_sorted = 1;
	if (stack->b.size != 0)
	{
		while (stack->b.size > 0)
		{
			cur = pop(&stack->b, BOT);
			temp = cur;
			cur = cur->prev;
			free(temp);
		}
		is_sorted = 0;
	}
	if (stack->a.size != 0)
	{
		while (stack->a.size > 0)
		{
			cur = pop(&stack->a, TOP);
			
			if (val <= cur->val)
				val = cur->val;
			else
				is_sorted = 0;
			temp = cur;
			cur = cur->prev;
			free(temp);
		}
	}
	if (is_sorted == 0)
		ft_printf("KO");
	else
		ft_printf("OK");
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
	else if (!ft_strncmp("rr\n", command, 3))
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

size_t	put_value_in_stack_a(int argc, char **argv, t_stack *a)
{
	int		cnt;
	int		result;
	int		nothing;
	t_node	*node;

	cnt = 1;
	while (cnt < argc)
	{
		result = atoi_fit(&argv[cnt], &nothing);
		if (argv[cnt][0] == '\0')
		{
			cnt++;
			if (cnt < argc && argv[cnt][0] == '\0')
				terminate();
		}
		if (nothing == 0)
		{
			node = (t_node *)malloc(sizeof(t_node));
			if (node == NULL)
				exit(1);
			node->val = result;
			push(a, node, BOT);
		}
	}
	return (a->size);
}

// test code

int main(int argc, char **argv)
{
	t_total	stack;
	t_node	*temp;
	char	*command;
	int		is_eof;

//	atexit(leaks);
	ft_memset(&stack, 0, sizeof(t_total));
	stack.size = put_value_in_stack_a(argc, argv, &stack.a);

	is_eof = 0;
	while (!is_eof)
	{
		command = get_next_line(0);
		is_eof = command_to_stack(&stack, command);
		if (command != NULL)
			free(command);
	}

	check_stack_sorted(&stack);

	return (0);
}




