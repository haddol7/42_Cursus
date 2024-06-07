/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:07:27 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/08 07:12:23 by jungslee         ###   ########.fr       */
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

void	replace_str(char **str, int start, int end, char *content)
{
	// char	*cpy;
	char	*tmp1;
	char	*tmp2;
	int		end_tmp;

	tmp1 = env_strcpy(0, start - 1, *str);
	tmp2 = ft_strjoin(tmp1, content);
	if (tmp2 == NULL)
		handle_error("exit : malloc error1", 1, 0);
	free(tmp1);
	tmp1 = env_strcpy(end + 1, ft_strlen(*str) - 1, *str);
	free(*str);
	*str = ft_strjoin(tmp2, tmp1);
	// cpy = ft_strjoin(tmp2, tmp1);
	if (*str == NULL)
		handle_error("exit : malloc error2", 1, 0);
	free(tmp1);
	free(tmp2);
	// return (cpy);
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

char	*change_env(char *cmd, int idx, t_env *env, int check_end)
{
	int		i;
	char	*cpy;
	char	*value;
	int		key_len;

	i = idx;
	key_len = 0;
	cpy = env_strcpy(0, ms_strlen(cmd) - 1, cmd);
	while (i < check_end)
	{
		if (cmd[i] == '$'&& is_exception(cmd, i) == 0)
		{
			value = env_validity(cmd, i, env, &key_len);
			if (value == NULL)
				replace_str(&cpy, i, i + key_len, "");
			else
				replace_str(&cpy, i, i + key_len, value);
			i += key_len;
		}
		i++;
	}
	return (cpy);
}

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



char *single_quote(char *cmd, int *idx, char *words_tmp)
{
	int		i;
	int		quote_start;
	int		quote_close;
	char	*in_quote;
	char	*cpy;

	i = 1;
	quote_start = *idx;
	while (cmd[quote_start + i] != '\'')
		i++;
	quote_close = quote_start + i;
	in_quote = env_strcpy(quote_start + 1, quote_close - 1, cmd);
	cpy = ms_strjoin(words_tmp, in_quote);
	*idx = quote_close + 1;
	free(in_quote);
	if (words_tmp != NULL)
		free(words_tmp);
	return (cpy);
}

char	*double_quote(char *cmd, int *idx, char *words_tmp, t_env *env)
{
	int		i;
	int		quote_start;
	int		quote_close;
	char	*tmp1;
	char	*tmp2;

	i = 1;
	quote_start = *idx;
	while (cmd[quote_start + i] != '\"')
		i++;
	quote_close = quote_start + i;
	tmp1 = env_strcpy(quote_start + 1, quote_close - 1, cmd);
	tmp2 = change_env(tmp1, *idx, env, ms_strlen(tmp1));
	free(tmp1);
	tmp1 = ms_strjoin(words_tmp, tmp2);
	*idx = quote_close + 1;
	free(tmp2);
	if (words_tmp != NULL)
		free(words_tmp);
	return (tmp1);
}

// char *normal_words(char *cmd, int *idx, t_env *env)
// {
// 	int		i;
// 	char	*ret;

// 	i = *idx;
// 	while (!(cmd[i] == '\'' || cmd[i] == '\"' || cmd[i] == '\-'))
// 	{
// 		if (cmd[i] == '$')
// 		{
// 			if (!(cmd[i + 1] == '\"' || \
// 					cmd[i + 1] == '\0' || cmd[i + 1] == '$'))
// 				ret = is_valid_env(cmd, &i, env);
// 			continue ;
// 		}
// 		i++;
// 	}
// 	if (ret == NULL)
// 		return (cmd);
// 	else
// 		free(cmd);
// 	*idx = i - 1;
// 	return (ret);	
// }

int	no_quote_env(char *cmd, int *idx, t_env *env, char *tmp)
{
	char	*replace;
	char	**split;
	char	*ret;
	int		len;

	len = 1;
	while (!(cmd[*idx + len] == '\'' || cmd[*idx + len] == '\"' || \
				cmd[*idx + len] == '\0'))
		len++;
	replace = change_env(cmd, *idx, env, *idx + len - 1);

	// ret = replace_str(cmd, *idx, *idx + len, replace);
	*idx = *idx + len;
	// return (replace);
	// split = ft_split(replace, " ");
}

void	handle_quote(t_node *node, t_env *env)
{
	int		i;
	int		j;
	char	*words_tmp;
	t_new_cmd	*head;

	i = 0;
	words_tmp = NULL;
	while (node->cmd[i] != NULL)
	{
		j = 0;
		while (node->cmd[i][j] != '\0')
		{
			if (node->cmd[i][j] == '\'')
				words_tmp = single_quote(node->cmd[i], &j, words_tmp);
			else if (node->cmd[i][j] == '\"')
				words_tmp = double_quote(node->cmd[i], &j, words_tmp, env);
			// else
			// {
			// 	words_tmp = no_quote_env(node->cmd[i], &j, env);
			// }
			// printf("############## %s\n", words_tmp);
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
		// is_var(node, env);
		handle_quote(node, env);
		// is_wild_card(node);
		return ;
	}
	check_cmd_node(node->right, env);
	check_cmd_node(node->left, env);
}

//TODO 중요한점 : 서브쉘을 실행할 때 우리가 수정한 환경변수가 자식 프로세스?? 에  전달이 되어야함. 그그니니까  할당한  env가 전달되어야함.

//TODO
//1. 