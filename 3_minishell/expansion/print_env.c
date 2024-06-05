/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:07:27 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/05 13:25:46 by jungslee         ###   ########.fr       */
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

char	*is_valid_env(char *ori, int *idx, t_env *env)
{
	t_env	*tmp;
	int		start;
	int		end;
	char	*ret;

	tmp = env;
	start = (*idx)++;
	ret = NULL;
	while (ft_isalnum(*(ori + *idx)) || ori[*idx] == '_')
		(*idx)++;
	end = *idx - 1;
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
	*idx = end + 1;
	free(ori);
	return (ret);
}

void	is_var(t_node *node, t_env *env)
{
	int		i;
	int		j;
	char	*content;
	int		quote;

	i = 0;
	quote = 0;
	while (node->cmd[i] != NULL)
	{
		j = 0;
		while (node->cmd[i][j] != '\0')
		{
			if (node->cmd[i][j] == '$')
			{
				// if (node->cmd[i][j + 1] == '$')
				// 	handle_error("해당 쉘의 pid 출력해야하는데 방법이 없음.", 1, 0);//TODO 의논해
				if (!(node->cmd[i][j + 1] == '\"' || \
						node->cmd[i][j + 1] == '\0' || node->cmd[i][j + 1] == '$'))
					node->cmd[i] = is_valid_env(node->cmd[i], &j, env);
			}
			j++;
		}
		i++;
	}
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


char *single_quote(char *cmd, int *start)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(cmd) - 1));
	if (tmp == NULL)
		handle_error("exit : malloc error", 1, 0);
	ft_memcpy(tmp, cmd, *start);
	while (cmd[*start + i] != '\'')
		i++;
	ft_memcpy(tmp + (*start), cmd + (*start) + 1, i - 1);
	// ft_memcpy(tmp + (*start) + i - 1, cmd + (*start) + i + 1, );
	*start = *start + i - 1;
	tmp[ft_strlen(cmd) - 3] = '\0';
	free(cmd);
	return (tmp);
}

void	handle_quote(t_node *node, t_env *env)
{
	int		i;
	int		j;
	char	*no_quote;

	i = 0;
	no_quote = NULL ;
	while (node->cmd[i] != NULL)
	{
		j = 0;
		while (node->cmd[i][j] != '\0')
		{
			if (node->cmd[i][j] == '\'')
			{
				printf("cmd ::::::: %s\n", node->cmd[i]);
				node->cmd[i] = single_quote(node->cmd[i], &j);
				printf("cmd ::::::: %s\n", node->cmd[i]);
			}
			else
				j++;
			// else if (node->cmd[i][j] == '\"')
			// // 	no_quote = double_quote(node->cmd[i], &j);
			// if (no_quote == NULL)
			// 	handle_error("exit : malloc error", 1, 0);
			// if (node->cmd[i][j] == '\'')
			// {
			// 	while (node->cmd[i][j] != '\'')
			// 		j++;
			// }
			// else if (node->cmd[i][j] == '\"')
			// {
			// 	while (node->cmd[i][j] != '\"')
			// 	{
			// 		if (node->cmd[i][j] == '$')
			// 			no_quote = is_valid_env(node->cmd[i], &j, env);
			// 		j++;
			// 	}
			// }
		}
		// free(node->cmd[i]);
		// node->cmd[i] = no_quote;
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
		// handle_quote(node, env);
		is_var(node, env);
		// is_wild_card(node);
		return ;
	}
	check_cmd_node(node->right, env);
	check_cmd_node(node->left, env);
}

//TODO 중요한점 : 서브쉘을 실행할 때 우리가 수정한 환경변수가 자식 프로세스?? 에  전달이 되어야함. 그그니니까  할당한  env가 전달되어야함.

//TODO
//1. 