/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:43:46 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/10 21:44:38 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*env_strcpy(int start, int end, char *str)
{
	char	*ret;
	int		i;

	i = 0;
	// printf("🎨🎨 : %s\n", str);
	// printf("$@@ START: %d, END : %d\n", start, end);

	ret = (char *)malloc(sizeof(char) * (end - start + 1));
	if (ret == NULL)
		handle_error("exit : malloc error4", 1, 0);
	
	while (start + i < end)
	{
		ret[i] = str[start + i];
		// printf("%d-th %c\n", str[start + i]);
		i++;
	}
	ret[i] = '\0';
	// printf("🎨 : %s\n", str);
	return (ret);
}

t_env *env_cpy(char **envp)
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
		name = env_strcpy(0, j, envp[i]);
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

int	is_alpha_num(char *var)
{
	int	i;
	int	quote_flag;

	i = 0;
	quote_flag = 0;
	while (var[i] != '\0')
	{
		if (!(ft_isalnum(var[i]) || var[i] == '_' || var[i] == '\"'))
			return (0);
		if (var[i] == '\"')
			quote_flag = 1;
		i++;
	}
	if (quote_flag == 1)
		return (2);
	return (1);
}
