/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:43:46 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/24 23:54:32 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "execution.h"
#include "builtin.h"
#include "minishell.h"

char	*ms_strcpy(int start, int end, char *str)
{
	char	*ret;
	int		i;

	i = 0;
	if (str == NULL)
		return (0);
	ret = (char *)ft_malloc(sizeof(char) * (end - start + 1));
	while (start + i < end)
	{
		ret[i] = str[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

t_env	*init_env_list(char **envp)
{
	char	*name;
	char	*content;
	int		i;
	int		j;
	t_env	*env;

	i = -1;
	env = NULL;
	while (envp[++i] != NULL)
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		name = ms_strcpy(0, j, envp[i]);
		content = ft_strdup(envp[i] + j + 1);
		env_add_back(&env, env_new(name, content));
	}
	env_update_shlvl(&env);
	content = env_update_pwd(&env);
	if (content != NULL)
		free(content);
	env_update_oldpwd(&env, NULL);
	return (env);
}

int	env_strncmp(char *s1, char *name, int n)
{
	if (name == NULL)
		return (1);
	while (n-- != 0 || *name != '\0')
	{
		if (*s1 != *name)
			return (1);
		s1++;
		name++;
	}
	if (*name != '\0')
		return (1);
	return (0);
}

char	*exit_status(void)
{
	char	*status;
	int		*int_status;

	int_status = get_status();
	status = ft_itoa(*int_status);
	return (status);
}

char	**env_join(t_env *ms_envp)
{
	char	**envp;
	t_env	*head;
	size_t	size;

	size = 1;
	head = ms_envp;
	while (head)
	{
		size++;
		head = head->next;
	}
	envp = ft_malloc(sizeof(char *) * (size));
	envp[size-- - 1] = NULL;
	while (size)
	{
		envp[size-- - 1] = env_join_key_value(ms_envp->key, ms_envp->value);
		ms_envp = ms_envp->next;
	}
	return (envp);
}
