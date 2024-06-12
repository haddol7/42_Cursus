/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:43:46 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/12 23:09:52 by daeha            ###   ########.fr       */
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

t_env	*env_cpy(char **envp)
{
	char	*name;
	char	*content;
	int		i;
	int		j;
	t_env	*env;

	i = 0;
	env = NULL;
	printf("1\n");
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
		printf("name %s content %s\n", name, content);
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
