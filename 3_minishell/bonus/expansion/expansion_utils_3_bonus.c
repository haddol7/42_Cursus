/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_3_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 19:08:51 by daeha             #+#    #+#             */
/*   Updated: 2024/07/02 17:38:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"
#include "expansion_bonus.h"

void	env_update_oldpwd(t_env **env, char *old_pwd)
{
	t_env	*node;

	node = env_find_pointer("OLDPWD", *env);
	if (node == NULL)
		env_add_back(env, env_new(ft_strdup("OLDPWD"), old_pwd));
	else
	{	
		node->complete = 1;
		if (node->value)
			free(node->value);
		node->value = old_pwd;
		if (!old_pwd)
			node->complete = 0;
	}
}

char	*env_update_pwd(t_env **env)
{
	t_env	*node;
	char	*old_pwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	node = env_find_pointer("PWD", *env);
	if (node == NULL)
	{	
		env_add_back(env, env_new(ft_strdup("PWD"), pwd));
		old_pwd = NULL;
	}
	else
	{
		old_pwd = node->value;
		node->value = pwd;
	}
	return (old_pwd);
}

char	*env_find_value(char *key, t_env *envp)
{
	size_t	len_key;
	size_t	len_envp;

	len_key = ft_strlen(key);
	while (envp)
	{
		len_envp = ft_strlen(envp->key);
		if (len_key == len_envp && !ft_strncmp(key, envp->key, len_key))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

t_env	*env_find_pointer(char *key, t_env *envp)
{
	size_t	len_key;
	size_t	len_envp;

	len_key = ft_strlen(key);
	while (envp)
	{
		len_envp = ft_strlen(envp->key);
		if (len_key == len_envp && !ft_strncmp(key, envp->key, len_key))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}
