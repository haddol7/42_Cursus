/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 00:45:28 by daeha             #+#    #+#             */
/*   Updated: 2024/06/16 03:12:15 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void		swap_string(char **str1, char **str2);
static t_env	*env_bubble_sort(t_env *env);
static t_env	*env_copy_for_sorts(t_env *env);

void	display_declare_list(t_env *env)
{
	t_env	*sorted;
	t_env	*temp;

	sorted = env_bubble_sort(env);
	while (sorted)
	{
		printf("declare -x %s=\"%s\"\n", sorted->key, sorted->value);
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
