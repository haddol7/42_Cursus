/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:41:48 by daeha             #+#    #+#             */
/*   Updated: 2024/06/18 16:39:31 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_status;

static int	exit_atoi(char *str);
static void	error_exit(char *str);

void	ms_exit(char **arg)
{
	int		status;
	char	*nbr;

	nbr = arg[1];
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (nbr == NULL)
		exit(g_status);
	status = exit_atoi(nbr);
	if (arg[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		g_status = EXIT_FAILURE;
		return ;
	}
	if (status >= 0)
		status = status % 256;
	else
		status = 256 + (status % 256);
	exit(status);
}

static char	*move_to_num(char *str, int *sign)
{
	while (*str != 0 && \
	(*str == '\t' || *str == '\n' || *str == ' ' || \
	*str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	if (*str == '-')
	{
		*sign = -1;
		return (++str);
	}
	else if (*str == '+')
		return (++str);
	return (str);
}

static int	exit_atoi(char *str)
{
	long	result;
	int		sign;
	char	*trimed_str;
	char	*nbr;

	sign = 1;
	result = 0;
	trimed_str = ft_strtrim(str, " ");
	nbr = move_to_num(trimed_str, &sign);
	while (*nbr >= '0' && *nbr <= '9')
	{
		result *= 10;
		result += *nbr - '0';
		if (result < 0)
			error_exit(str);
		nbr++;
	}
	if (*nbr != '\0')
		error_exit(str);
	free(trimed_str);
	return ((int)(sign * result));
}

static void	error_exit(char *str)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit(255);
}
