/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:07:27 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/02 10:34:16 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*replace_env(char *str, int start, int end, char *content)
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
					handle_error("해당 쉘의 pid 출력해야하는데 방법이 없음.", 1, 0);//TODO 의논해
				else if (!(node->cmd[i][j + 1] == '\"' || \
						node->cmd[i][j + 1] == '\0'))
					node->cmd[i] = is_valid_env(node->cmd[i], j, env);
			}
			j++;
		}
		i++;
	}
}

void	check_cmd_node(t_node *ast, t_env *env)//TODO exit status 구현하기
{
	t_node	*node;
	char	*var;

	node = ast;
	if (node->type == N_CMD)
	{
		is_var(node, env);
		is_wild_card(node);
		return ;
	}
	check_cmd_node(node->right, env);
	check_cmd_node(node->left, env);
}
