/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:27:14 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/02 10:29:51 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*env_strcpy(int start, int end, char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *)malloc(sizeof(char) * (end - start + 2));
	if (ret == NULL)
		handle_error("exit : malloc error", 1, 0);
	while (start + i <= end)
	{
		ret[i] = str[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	env_cpy(t_env **env, char **envp)
{
	char	*name;
	char	*content;
	int		i;
	int		j;
	int		equal_idx;

	i = 0;
	equal_idx = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		equal_idx = j;
		name = env_strcpy(0, j - 1, envp[i]);
		content = ft_strdup(envp[i] + j + 1);
		if (name == NULL || content == NULL)
			handle_error("exit : malloc error", 1, 0);
		env_add_back(env, env_new(name, content));
		i++;
	}
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

// #include <stdio.h>
//
// void	print_all_env(t_env *head)//TODO ㅈㅣ우ㅓ
// {
// 	t_env	*to_print;
// 	int		i;
//
// 	to_print = head;
// 	i = 1;
// 	while (to_print != NULL)
// 		to_print = to_print->next;
// }
