/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:43:46 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/14 23:20:17 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*ms_strcpy(int start, int end, char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *)malloc(sizeof(char) * (end - start + 1));
	if (ret == NULL)
		handle_error("exit : malloc error4", 1, 0);
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

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		name = ms_strcpy(0, j, envp[i]);
		content = ft_strdup(envp[i] + j + 1);
		if (name == NULL || content == NULL)
			handle_error("exit : malloc error5", 1, 0);
		env_add_back(&env, env_new(name, content));
		i++;
	}
	return (env);
}

int	env_strncmp(char *s1, char *name, int n)
{
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

//these below funtions are used in e_cmd.c
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

char	*env_join_key_value(char *key, char *value)
{
	char	*temp;
	char	*str;

	temp = ft_strjoin(key, "=");
	str = ft_strjoin(temp, value);
	free(temp);
	return (str);
}
