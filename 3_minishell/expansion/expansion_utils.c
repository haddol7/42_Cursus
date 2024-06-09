/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:43:46 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/09 20:50:30 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*env_strcpy(int start, int end, char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *)malloc(sizeof(char) * (end - start + 2));
	// printf("end - start ::: %d\n", end - start + 2);
	if (ret == NULL)
		handle_error("exit : malloc error4", 1, 0);
	while (start + i <= end)
	{
		ret[i] = str[start + i];
		i++;
	}
	ret[i] = '\0';
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
	// printf("NO1\n");
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		// printf("NO\n");
		name = env_strcpy(0, j - 1, envp[i]);
		// printf("NO\n");
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

// char	*ms_strjoin(char const *s1, char const *s2)
// {
// 	char	*str;
// 	size_t	s1_len;
// 	size_t	s2_len;

// 	if (s1 == NULL || s2 == NULL)
// 		return (NULL);
// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	str = (char *)ft_malloc((s1_len + s2_len + 1) * sizeof(char));
// 	if (str == NULL)
// 		handle_error("exit : malloc error", 1, 0);
// 	ft_memmove(str, s1, s1_len);
// 	ft_memmove(str + s1_len, s2, s2_len + 1);
// 	return (str);
// }

// #include <stdio.h>
//
// void	print_all_env(t_env *head)//TODO ㅈㅣ우ㅓ
// {
// 	t_env	*to_print;
// 	int		i;

// 	to_print = head;
// 	i = 1;
// 	while (to_print != NULL)
// 		to_print = to_print->next;
// }
