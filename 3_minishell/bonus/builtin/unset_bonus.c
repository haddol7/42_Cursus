/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:31:54 by daeha             #+#    #+#             */
/*   Updated: 2024/07/02 17:38:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"
#include "execution_bonus.h"
#include "minishell_bonus.h"

static void		env_del_node(char *arg, t_env *env);
static void		swap_contents_without_change_node(t_env *env);
static t_bool	is_env_key_valid(char *str);

void	ms_unset(char **arg, t_env *env)
{
	t_bool	error;

	arg++;
	error = FALSE;
	while (*arg)
	{
		if (is_env_key_valid(*arg))
			env_del_node(*arg, env);
		else
			error = TRUE;
		arg++;
	}
	if (error)
		set_status(EXIT_FAILURE);
	else
		set_status(EXIT_SUCCESS);
}

static void	env_del_node(char *arg, t_env *env)
{
	t_env	*node;

	node = env_find_pointer(arg, env);
	if (node == NULL)
		return ;
	free(node->key);
	node->key = NULL;
	if (node->complete)
		free(node->value);
	node->value = NULL;
	if (env == node)
		swap_contents_without_change_node(env);
	else
	{
		while (env->next != node)
			env = env->next;
		env->next = node->next;
		free(node);
	}
}

static void	swap_contents_without_change_node(t_env *env)
{
	t_env	*temp;

	if (env->next == NULL)
		return ;
	temp = env->next;
	env->key = temp->key;
	env->value = temp->value;
	env->complete = temp->complete;
	env->next = temp->next;
	temp->key = NULL;
	temp->value = NULL;
	temp->next = NULL;
	free(temp);
}

static t_bool	is_env_key_valid(char *str)
{
	size_t	i;

	i = 1;
	if (str[0] != '_' && !ft_isalpha(str[0]))
	{
		error_cmd_exit(str, EVALUE);
		return (FALSE);
	}
	while (str[i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
		{
			error_cmd_exit(str, EVALUE);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
