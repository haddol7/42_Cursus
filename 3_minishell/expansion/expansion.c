/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:07:27 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/11 22:32:00 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

// char	*ms_strlcpy(char *src, int len)
// {
// 	char	*dest;
// 	int		i;

// 	i = 0;
// 	dest = (char *)malloc(sizeof(char) * (len + 1));
// 	while (i < len)
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

char	*return_value(char *dollar_start, t_env *env)
{
	int		i;
	char	*value;
	int		key_len;

	i = 1;
	key_len = 0;
	value = NULL;
	if (ft_isalnum(dollar_start[i]) == 0)
		return (0);
	while (ft_isalnum(dollar_start[i]) || dollar_start[i] == '_')
		i++;
	key_len = i - 1;
	while (env != NULL)
	{
		if (env_strncmp(dollar_start + 1, env->key, i - 1) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*replace_cmd(char *origin, char **value, int *dollar_idx)
{
	char	*part1;
	char	*part2;
	char	*result;
	char	*tmp;
	int		del_len;

	del_len = 1;
	while (ft_isalnum(*(origin + *dollar_idx + del_len)) || \
			*(origin + *dollar_idx + del_len) == '_')
		del_len++;
	part1 = ms_strcpy(0, *dollar_idx, origin);
	tmp = ft_strjoin(part1, *value);
	part2 = ms_strcpy(*dollar_idx + del_len, ms_strlen(origin), origin);
	result = ft_strjoin(tmp, part2);
	*dollar_idx = ms_strlen(tmp) - 1;
	printf("🥇result is ----------> %s\n", result);
	printf("🥇value  is ----------> %s\n", *value);

	free(tmp);
	free(part1);
	free(part2);
	free(origin);
	free(*value);
	*value = NULL;
	return (result);
}

// void	quote_lock(char c, int *status)
// {
// 	if (*status == 0)
// 	{
// 		if (c == '\'')
// 			*status = 1;
// 		if (c == '\"')
// 			*status = 2;
// 	}
// 	else if (*status == 1)
// 	{
// 		if (c == '\'')
// 			*status = 0;
// 	}
// 	else if (*status == 2)
// 	{
// 		if (c == '\"')
// 			*status = 0;
// 	}
// }

void	add_list(t_new_cmd **list, char *new_cmd)
{
	int		i;
	int		start;
	int		quote;
	char	*split;

	i = 0;
	start = 0;
	quote = 0;
	while (new_cmd[i] != '\0')
	{
		quote_lock(new_cmd[i], &quote);
		if (quote == 0 && new_cmd[i] == ' ')
		{
			split = ms_strcpy(start, i, new_cmd);
			cmd_add_back(list, split);
			while (new_cmd[i] == ' ')
				i++;
			start = i;
			continue ;
		}
		else
			i++;
	}
	split = ms_strcpy(start, i, new_cmd);
	cmd_add_back(list, split);
}

void	expand_dollar(char *cmd, t_env *env, t_new_cmd **list)
{
	int		j;
	int		quote;
	char	*expand_value;
	char	*new_cmd;

	j = 0;
	new_cmd = ft_strdup(cmd);
	while (new_cmd[j] != '\0')
	{
		quote_lock(new_cmd[j], &quote);
		if (new_cmd[j]  == '$' && quote != 1)
		{
			expand_value = return_value(new_cmd + j, env);
			printf("expand_value is %s\n", expand_value);
			if (expand_value != NULL)
				new_cmd = replace_cmd(new_cmd, &expand_value, &j);
		}
		j++;
		printf("J :: %d-th index %s\n", j, new_cmd);
	}
	//printf("new_cmd :::::; %s \nlen ::: %d\n", new_cmd, ms_strlen(new_cmd));
	add_list(list, new_cmd);
	free(new_cmd);
}
//TODO : "$TEST" -> fix replace_cmd
void	expand_one_node(char **cmd, t_env *env, t_new_cmd **list)
{
	int			i;
	// t_new_cmd	*next;

	// list = NULL;
	i = 0;
	while (cmd[i] != NULL)
	{
		printf("cmd :::::::: %s\n", cmd[i]);
		expand_dollar(cmd[i], env, list);
		i++;
	}
   	expand_quote(*list, env);
	print_all_cmd(*list);
	// expand_asterisk(list, env);
	// next = cmd_last(list);
}



// void	expand_one_node(char **cmd, t_env *env, t_new_cmd **list_head)
// {
// 	int	 		i;
// 	t_new_cmd	*last;

// 	i = 0;
// 	last = *list_head;
// 	while (cmd[i] != NULL)
// 	{
// 		expand_one_cmd(cmd[i], env, &last);
// 		i++;
// 	}
// }

void	expansion(t_node *ast, t_env *env)//TODO exit status 구현하기
{
	t_new_cmd	*list;
	char		**new_cmd;

	list = NULL;
	if (ast == NULL)
		return ;
	if (ast->type == N_CMD)
	{
		// printf("AJEHWT??");
		expand_one_node(ast->cmd, env, &list);
		// check_env_and_expand(node, env, &new_list);
		// //handle_quote(new_list, env);
		new_cmd = cpy_list_to_cmd(list);
		list_free_all(&list);
		free_all_old_cmd(ast->cmd);
		ast->cmd = new_cmd;
		return ;
		// node->cmd = new_cmd;
		// // printf("@TSG");
		// return ;
	}
	expansion(ast->right, env);
	expansion(ast->left, env);
}


// while (cmd[i])
//     expand_one_cmd(cmd[i++], list, env);

// expand_one_cmd(char *origin, t_list expanded_cmd, t_env env)
// {
//     origin = expand_dollar(origin, expanded_cmd, env);
//     origin = expand_quote(origin, expanded_cmd, env);
// }

//     origin = expand_asterisk(origin, expanded_cmd, env);

// char	*env_validity(char *cmd, int idx, t_env *env, int *key_len)
// {
// 	int		start;
// 	int		end;

// 	start = idx++;
// 	while (ft_isalnum(*(cmd + idx)) || cmd[idx] == '_')
// 		idx++;
// 	end = idx - 1;
// 	*key_len = end - start + 1;
// 	while (env != NULL)
// 	{
// 		if (env_strncmp(cmd + start + 1, env->key, end - start) == 0)
// 			return (env->value);
// 		env = env->next;
// 	}
// 	return (0);
// }

// //$PATH!!
// void	check_env_and_expand(t_node *node, t_env *env, t_new_cmd **list)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	str = NULL;
// 	while (node->cmd[i] != NULL)
// 	{
// 		// printf("node_cmd :: %s\n", node->cmd[i]);
// 		// str = ft_strdup(node->cmd[i]);
// 		// printf("str 1:: %s\n", str);
// 		str = find_dollar_and_expand(node->cmd[i], env);
// 		// printf("str 2 ::");
// 		if (str[0] == '\0')
// 		{
// 			free(str);
// 			str = NULL;
// 			i++;
// 			continue ;
// 		}
// 		else
// 			ms_split(str, list);
// 		i++;
// 		// printf("expanded :::: %s\n", str);
// 	}
// }

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
	result = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	while (i < word_cnt)
	{
		if (tmp->cmd != NULL && tmp->cmd[0] != '\0')
			result[i] = ft_strdup(tmp->cmd);
		tmp = tmp->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

// void	expansion(t_node *ast, t_env *env)//TODO exit status 구현하기
// {
// 	t_node	*node;
// 	char	*var;
// 	t_new_cmd	*new_list;
// 	char	**new_cmd;

// 	node = ast;
// 	new_list = NULL;
// 	if (ast == NULL)
// 		return ;
// 	if (node->type == N_CMD)
// 	{
// 		check_env_and_expand(node, env, &new_list);
// 		//handle_quote(new_list, env);
// 		new_cmd = cpy_list_to_cmd(new_list);
// 		list_free_all(&new_list);
// 		free_all_old_cmd(node->cmd);
// 		node->cmd = new_cmd;
// 		// printf("@TSG");
// 		return ;
// 	}
// 	expansion(node->right, env);
// 	expansion(node->left, env);
// }

// //TODO 중요한점 : 서브쉘을 실행할 때 우리가 수정한 환경변수가 자식 프로세스?? 에  전달이 되어야함. 그그니니까  할당한  env가 전달되어야함.

// //TODO
// //1. 
