/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 00:45:28 by daeha             #+#    #+#             */
/*   Updated: 2024/06/25 04:37:33 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"

static void		swap_string(char **str1, char **str2);
static t_env	*env_bubble_sort(t_env *env);
static t_env	*env_copy_for_sorts(t_env *env);
static void		swap_int(int *a, int *b);

void	display_declare_list(t_env *env)
{
	t_env	*sorted;
	t_env	*temp;

	sorted = env_bubble_sort(env);
	while (sorted)
	{	
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(sorted->key, STDOUT_FILENO);
		if (sorted->complete == 1)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(sorted->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		temp = sorted->next;
		free(sorted);
		sorted = temp;
	}
}

static t_env	*env_bubble_sort(t_env *env)
{
	t_env	*sorted;
	t_env	*i;
	t_env	*j;

	sorted = env_copy_for_sorts(env);
	i = sorted;
	while (i)
	{	
		j = sorted;
		while (j && j->next)
		{
			if (ft_strcmp(j->key, j->next->key) > 0)
			{
				swap_string(&j->key, &j->next->key);
				swap_string(&j->value, &j->next->value);
				swap_int(&j->complete, &j->next->complete);
			}
			j = j->next;
		}
		i = i->next;
	}
	return (sorted);
}

static t_env	*env_copy_for_sorts(t_env *env)
{
	t_env	*cur;
	t_env	*sorted;

	cur = env;
	sorted = NULL;
	while (cur)
	{
		env_add_back(&sorted, env_new(cur->key, cur->value));
		cur = cur->next;
	}
	return (sorted);
}

static void	swap_string(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

static void	swap_int(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
