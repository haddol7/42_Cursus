/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:07:27 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/09 21:29:19 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int	ms_strlen(char *str)
{
	int	cnt;

	cnt = 0;
	while (!(str == NULL || str[cnt] == '\0'))
		cnt++;
	return (cnt);
}

char	*ms_strjoin(char *s1, char *s2)
{
	char	*str;
	int		idx;
	int		s1_len;
	int		s2_len;

	idx = 0;
	s1_len = ms_strlen(s1);
	s2_len = ms_strlen(s2);
	str = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (str == NULL)
		handle_error("exit : malloc error", 1, 0);
	while (idx < s1_len)
	{
		str[idx] = s1[idx];
		idx++;
	}
	while (idx < s1_len + s2_len)
	{
		str[idx] = s2[idx - s1_len];
		idx++;
	}
	str[idx] = '\0';
	return (str);
}

// char	*replace_str(char *cmd, int start, int end, char *value)
// {
// 	char	*tmp1;
// 	char	*tmp2;
// 	char	*result;

// 	tmp1 = env_strcpy(0, start - 1, *cmd);
// 	tmp2 = ft_strjoin(tmp1, value);
// 	if (tmp2 == NULL)
// 		handle_error("exit : malloc error1", 1, 0);
// 	free(tmp1);
// 	tmp1 = env_strcpy(end + 1, ft_strlen(*cmd) - 1, *cmd);
// 	result = ft_strjoin(tmp2, tmp1);
// 	if (result == NULL)
// 		handle_error("exit : malloc error2", 1, 0);
// 	free(tmp1);
// 	free(tmp2);
// 	return (result);
// }

char	*replace_str(char *cmd, int start, char *value, int quote)
{
	char	*tmp;
	char	*result1;
	char	*result2;

	tmp = env_strcpy(0, start - 1, cmd);
	result1 = ft_strjoin(tmp, value);
	if (result1 == NULL)
		handle_error("exit : malloc error1", 1, 0);
	free(tmp);
	if (quote != 0)
	{
		result2 = ft_strjoin(result1, "\"");
		if (result2 == NULL)
			handle_error("exit : malloc error", 1, 0);
		free(result1);
		return (result2);
	}
	return (result1);
}

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

int	is_exception(char *cmd, int idx)
{
	if (cmd[idx + 1] == '\"' || \
				cmd[idx + 1] == '\0' || cmd[idx + 1] == '$')
		return (1);
	return (0);
}

// void	is_var(t_node *node, t_env *env)
// {
// 	int		i;
// 	int		j;
// 	char	*content;
// 	int		single_quote;

// 	i = 0;
// 	single_quote = -1;
// 	while (node->cmd[i] != NULL)
// 	{
// 		j = 0;
// 		while (node->cmd[i][j] != '\0')
// 		{
// 			if (node->cmd[i][j] == '\'')
// 				single_quote *= -1;
// 			if (single_quote == -1 && node->cmd[i][j] == '$')
// 			{
// 				if (!(node->cmd[i][j + 1] == '\"' || \
// 						node->cmd[i][j + 1] == '\0' || node->cmd[i][j + 1] == '$'))
// 					node->cmd[i] = is_valid_env(node->cmd[i], &j, env);
// 				continue ;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }


// char	*replace_env(char *cmd, int idx, t_env *env)
// {
// 	int	start;
// 	int	end;

// 	if (is_exception(cmd, idx) == 0)
// 		return (0);
// 	start = idx++;
// 	while (ft_isalnum(*(cmd _ idx)) || cmd[idx] == '_')
// 		idx++;
// 	end = idx - 1;
// 	while (env != NULL)
// 	{
// 		if (env_strncmp(cmd + start + 1, env->key, end - start) == 0)
// 			replace_str(cmd, )
// 		env = env->next;
// 	}
// }

char	*replace_env(char *cmd, int *idx, t_env *env, int quote)
{
	int	start;
	int	end;
	char	*expand;

	start = (*idx)++;
	expand = NULL;
	while (ft_isalnum(*(cmd + *idx)) || cmd[*idx] == '_')
		(*idx)++;
	end = *idx - 1;
	*idx = end - start + 1;// TODO 이렇게 하면 부모함수에서 j++ 해줘야 함.
	while (env != NULL)
	{
		if (env_strncmp(cmd + start + 1, env->key, end - start) == 0)
		{
			expand = replace_str(cmd, start, env->value, quote);
			break ;
		}
		env = env->next;
	}
	if (expand == NULL)
		expand = replace_str(cmd, start, "", quote);
	return (expand);
}

// char	*replace_env(char *cmd, int idx, t_env *env)
// {
// 	int		i;
// 	char	*cpy;
// 	char	*value;
// 	int		key_len;

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

// 	i = idx;
// 	key_len = 0;
// 	cpy = env_strcpy(0, ms_strlen(cmd) - 1, cmd);
// 	while (i < check_end)
// 	{
// 		if (cmd[i] == '$'&& is_exception(cmd, i) == 0)
// 		{
// 			value = env_validity(cmd, i, env, &key_len);
// 			if (value == NULL)
// 				replace_str(&cpy, i, i + key_len, "");
// 			else
// 				replace_str(&cpy, i, i + key_len, value);
// 			i += key_len;
// 		}
// 		i++;
// 	}
// 	return (cpy);
// }

// char *single_quote(char *no_quote, char *cmd, int *start)
// {
// 	int		len;
// 	int		i;
// 	int		j;
// 	char	*del_quote;

// 	i = 1;
// 	while (cmd[*start + i] != '\'')
// 		i++;
// 	len = ft_strlen(no_quote) + i;
// 	del_quote = (char *)malloc(sizeof(char) * len);
// 	i = -1;
// 	while (no_quote[++i] != '\0')
// 		del_quote[i] = no_quote[i];
// 	j = 1;
// 	while (cmd[*start + j] != '\'')
// 	{
// 		del_quote[i] = cmd[*start + j];
// 		i++;
// 		j++;
// 	}
// 	del_quote[i] = '\0';
// 	free(no_quote);
// 	*start = *start + j + 1;
// 	return (del_quote);
// }


// char *single_quote(char *cmd, int *start)
// {
// 	char	*tmp;
// 	int		i;
// 	int		len;

// 	i = 0;
// 	tmp = (char *)malloc(sizeof(char) * (ft_strlen(cmd) - 1));
// 	if (tmp == NULL)
// 		handle_error("exit : malloc error", 1, 0);
// 	ft_memcpy(tmp, cmd, *start);
// 	while (cmd[*start + i] != '\'')
// 		i++;
// 	ft_memcpy(tmp + (*start), cmd + (*start) + 1, i - 1);
// 	// ft_memcpy(tmp + (*start) + i - 1, cmd + (*start) + i + 1, );
// 	*start = *start + i - 1;
// 	tmp[ft_strlen(cmd) - 3] = '\0';
// 	free(cmd);
// 	return (tmp);
// }]



char *de_quote(char *cmd, int *idx, char *words_tmp, char quote)
{
	int		i;
	int		quote_start;
	int		quote_close;
	char	*in_quote;
	char	*result;

	i = 1;
	quote_start = *idx;
	while (cmd[quote_start + i] != quote)
		i++;
	quote_close = quote_start + i;
	in_quote = env_strcpy(quote_start + 1, quote_close - 1, cmd);
	result = ms_strjoin(words_tmp, in_quote);
	*idx = quote_close + 1;
	free(in_quote);
	if (words_tmp != NULL)
		free(words_tmp);
	return (result);
}

// char	*double_quote(char *cmd, int *idx, char *words_tmp, t_env *env)
// {
// 	int		i;
// 	int		quote_start;
// 	int		quote_close;
// 	char	*tmp1;
// 	char	*tmp2;

// 	i = 1;
// 	quote_start = *idx;
// 	while (cmd[quote_start + i] != '\"')
// 		i++;
// 	quote_close = quote_start + i;
// 	tmp1 = env_strcpy(quote_start + 1, quote_close - 1, cmd);
// 	free(tmp1);
// 	tmp1 = ms_strjoin(words_tmp, tmp2);
// 	*idx = quote_close + 1;
// 	free(tmp2);
// 	if (words_tmp != NULL)
// 		free(words_tmp);
// 	return (tmp1);
// }

char	*no_quote(char *cmd, int *idx, char *words_tmp)
{
	int	i;
	char	*tmp;
	char	*result;
	int	start;
	int	end;

	i = 0;
	start = *idx;
	while (!(cmd[start + i] == '\'' || cmd[start + i] == '\"' || \
					cmd[start + i] == '\0'))
		i++;
	end = start + i - 1;
	tmp = env_strcpy(start, end, cmd);
	result = ms_strjoin(words_tmp, tmp);
	*idx = end + 1;
	// printf("idx, cmd[idx] : %d, %c\n", *idx, result[*idx]);//TODO 이게 맞ㅇ?
	free(tmp);
	if (words_tmp != NULL)
		free(words_tmp);
	return (result);
}


void	handle_quote(t_new_cmd *list, t_env *env)
{
	int		i;
	int		j;
	char	*words_tmp;

	while (list != NULL)
	{
		words_tmp = NULL;
		i = 0;
		while (list->cmd[i] != '\0')
		{
			if (list->cmd[i] == '\'' || list->cmd[i] == '\"')
				words_tmp = de_quote(list->cmd, &i, words_tmp, list->cmd[i]);
			else
				words_tmp = no_quote(list->cmd, &i, words_tmp);
			// else if (node->cmd[i][j] == '\"')
			// 	words_tmp = double_quote(node->cmd[i], &j, words_tmp, env);
			// else
			// {
			// 	words_tmp = no_quote_env(node->cmd[i], &j, env);
			// }
			// printf("############## %s\n", words_tmp);
			
		}
		free(list->cmd);
		printf("word tmp ::%s\n", words_tmp);
		list->cmd = words_tmp;
		list = list->next;
	}
}

void	quote_lock(char c, int *status)
{
	if (*status == 0)
	{
		if (c == '\'')
			*status = 1;
		if (c == '\"')
			*status = 2;
	}
	else if (*status == 1)
	{
		if (c == '\'')
			*status = 0;
	}
	else if (*status == 2)
	{
		if (c == '\"')
			*status = 0;
	}
}

void	ms_split(char *str, t_new_cmd **list)
{
	int	i;
	int	start;
	char	*tmp;
	int	quote_status;

	i = 0;
	start = 0;
	quote_status = 0;
	while (1)
	{
		quote_lock(str[i], &quote_status);
		if (quote_status == 0 && str[i] == ' ')
		{
			cmd_add_back(list, env_strcpy(start, i - 1, str));
			// cmd_add_back(list, ft_strdup(" "));//TODO 일단 공백 1개만 포함.
			while (str[i] == ' ')
				i++;
			start = i;
		}
		if (str[i] == '\0')
		{
			cmd_add_back(list, env_strcpy(start, i - 1, str));
			break ;
		}
		i++;
	}
}

void	iter_cmd(char *cmd, int j, t_env *env, char **str)
{
	int		quote_status;
	int		key_len;

	quote_status = 0;
	key_len = 0;
	while (cmd[j] != '\0')
	{
		quote_lock(cmd[j], &quote_status);
		if ((cmd[j] == '$') && is_exception(cmd, j) == 0 && \
			quote_status != 1)
		{
			free(*str);
			*str = replace_env(cmd, &j, env, quote_status);
		}
		j++;
	}
}

void	check_env_and_replace(t_node *node, t_env *env, t_new_cmd **list)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	str = NULL;
	while (node->cmd[i] != NULL)
	{
		j = 0;
		str = ft_strdup(node->cmd[i]);
		iter_cmd(node->cmd[i], j, env, &str);
		ms_split(str, list);
		i++;
	}
	// print_all_cmd(*list);
}

char	**list_to_new_cmd(t_new_cmd *new_list)
{
	int	word_cnt;
	int	i;
	char	**result;
	t_new_cmd	*tmp;

	tmp = new_list;
	i = 0;
	word_cnt = get_cmd_node_num(new_list);
	result = (char **)malloc(sizeof(char) * (word_cnt + 1));
	while (i < word_cnt)
	{
		result[i] = ft_strdup(tmp->cmd);
		tmp = tmp->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

void	free_all_old_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	check_cmd_node(t_node *ast, t_env *env)//TODO exit status 구현하기
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
		check_env_and_replace(node, env, &new_list);
		// list_to_array()
		// print_all_cmd(new_list);;
		handle_quote(new_list, env);
		// is_wild_card(node);
		// print_all_cmd(new_list);
		new_cmd = list_to_new_cmd(new_list);
		list_free_all(&new_list);
		free_all_old_cmd(node->cmd);
		node->cmd = new_cmd;
		return ;
	}
	check_cmd_node(node->right, env);
	check_cmd_node(node->left, env);
}

//TODO 중요한점 : 서브쉘을 실행할 때 우리가 수정한 환경변수가 자식 프로세스?? 에  전달이 되어야함. 그그니니까  할당한  env가 전달되어야함.

//TODO
//1. 
