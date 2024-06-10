/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:07:27 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/10 18:39:25 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*env_validity(char *cmd, int idx, t_env *env, int *key_len)
{
	int		start;
	int		end;

	start = idx++;
	while (ft_isalnum(*(cmd + idx)) || cmd[idx] == '_')
		idx++;
	end = idx - 1;
	*key_len = end - start + 1;
	while (env != NULL)
	{
		if (env_strncmp(cmd + start + 1, env->key, end - start) == 0)
			return (env->value);
		env = env->next;
	}
	return (0);
}

void	check_env_and_expand(t_node *node, t_env *env, t_new_cmd **list)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (node->cmd[i] != NULL)
	{
		// printf("node_cmd :: %s\n", node->cmd[i]);
		str = ft_strdup(node->cmd[i]);
		// printf("str 1:: %s\n", str);
		find_dollar_and_expand(node->cmd[i], env, &str);
		// printf("str 2 ::");
		if (str[0] == '\0')
		{
			free(str);
			str = NULL;
			i++;
			continue ;
		}
		else
			ms_split(str, list);
		i++;
		printf("expanded :::: %s\n", str);
	}
}

char	**cpy_list_to_cmd(t_new_cmd *new_list)
{
	int	word_cnt;
	int	i;
	char	**result;
	t_new_cmd	*tmp;

	if (new_list == NULL)
		return (0);
	tmp = new_list;
	i = 0;
	word_cnt = get_cmd_node_num(new_list);
	result = (char **)malloc(sizeof(char) * (word_cnt + 1));
	while (i < word_cnt)
	{
		if (tmp->cmd != NULL)
			result[i] = ft_strdup(tmp->cmd);
		tmp = tmp->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

void	expansion(t_node *ast, t_env *env)//TODO exit status 구현하기
{
	t_node	*node;
	char	*var;
	t_new_cmd	*new_list;
	char	**new_cmd;

	node = ast;
	new_list = NULL;
	if (ast == NULL)
		return ;
	if (node->type == N_CMD)
	{
		check_env_and_expand(node, env, &new_list);
		handle_quote(new_list, env);
		new_cmd = cpy_list_to_cmd(new_list);
		list_free_all(&new_list);
		free_all_old_cmd(node->cmd);
		node->cmd = new_cmd;
		// printf("@TSG");
		return ;
	}
	expansion(node->right, env);
	expansion(node->left, env);
}

//TODO 중요한점 : 서브쉘을 실행할 때 우리가 수정한 환경변수가 자식 프로세스?? 에  전달이 되어야함. 그그니니까  할당한  env가 전달되어야함.

//TODO
//1. 
