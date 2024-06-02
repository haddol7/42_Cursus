/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:07:27 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/02 10:09:38 by jungslee         ###   ########.fr       */
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

#include <stdio.h>

void	print_all_env(t_env *head)//TODO ㅈㅣ우ㅓ
{
	t_env	*to_print;
	int		i;

	to_print = head;
	i = 1;
	while (to_print != NULL)
		to_print = to_print->next;
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

char	*replace_env(char *str, int start, int end, char *content)//TODO
{
	char	*ret;
	char	*tmp1;
	char	*tmp2;

	tmp1 = env_strcpy(0, start - 1, str);
	tmp2 = ft_strjoin(tmp1, content);
	if (tmp2 == NULL)
		handle_error("exit : malloc error", 1, 0);
	free(tmp1);
	tmp1 = env_strcpy(end + 1, ft_strlen(str) - 1, str);
	ret = ft_strjoin(tmp2, tmp1);
	if (ret == NULL)
		handle_error("exit : malloc error", 1, 0);
	free(tmp1);
	free(tmp2);
	return (ret);
}

char	*is_valid_env(char *ori, int idx, t_env *env)
{
	t_env	*tmp;
	int		start;
	int		end;
	char	*ret;

	tmp = env;
	start = idx++;
	ret = NULL;
	while (ft_isalnum(*(ori + idx)) || ori[idx] == '_')
		idx++;
	end = idx - 1;
	while (tmp != NULL)
	{
		if (env_strncmp(ori + start + 1, tmp->name, end - start) == 0)
		{
			ret = replace_env(ori, start, end, tmp->content);
			break ;
		}
		tmp = tmp->next;
	}
	if (ret == NULL)
		ret = replace_env(ori, start, end, "");
	free(ori);
	return (ret);
}

 
void	is_var(t_node *node, t_env *env)
{
	int		i;
	int		j;
	char	*content;

	i = 0;
	while (node->cmd[i] != NULL)
	{
		j = 0;
		while (node->cmd[i][0] != '\'' && node->cmd[i][j] != '\0')
		{
			if (node->cmd[i][j] == '$')
			{
				if (node->cmd[i][j + 1] == '$')
					handle_error("해당 쉘의 pid 출력해야하는데 방법이 없음.", 1, 0);//TODO 고쳐
				else if (!(node->cmd[i][j + 1] == '\"' || node->cmd[i][j + 1] == '\0'))
					node->cmd[i] = is_valid_env(node->cmd[i], j, env);
			}
			j++;
		}
		i++;
	}
}

void	check_env(t_node *ast, t_env *env)//TODO exit status 구현하기
{
	t_node	*node;
	char	*var;

	node = ast;
	if (node->type == N_CMD)
	{
		is_var(node, env);
		return ;
	}
	check_env(node->right, env);
	check_env(node->left, env);
}
