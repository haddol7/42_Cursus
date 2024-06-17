/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:07:27 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/17 18:44:55 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "execution.h"

void	expand_one_node(char **cmd, t_env *env, t_new_cmd **list)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		expand_dollar(cmd[i], env, list);
		i++;
	}
	wild_card(list);
	expand_quote(*list, env);
}

char	**cpy_list_to_cmd(t_new_cmd *new_list)
{
	int			word_cnt;
	int			i;
	char		**result;
	t_new_cmd	*tmp;

	if (new_list == NULL)
		return (0);
	tmp = new_list;
	word_cnt = get_cmd_node_num(new_list);
	result = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	i = 0;
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

void	expansion(t_node *ast, t_env *env)
{
	t_new_cmd	*list;
	char		**new_cmd;

	list = NULL;
	if (ast == NULL)
		return ;
	if (ast->type == N_CMD)
	{
		expand_one_node(ast->cmd, env, &list);
		new_cmd = cpy_list_to_cmd(list);
		list_free_all(&list);
		free_double_pointer(ast->cmd);
		ast->cmd = new_cmd;
		return ;
	}
	expansion(ast->right, env);
	expansion(ast->left, env);
}

void	cmd_expansion(t_node *node, t_env *env)
{
	t_new_cmd	*list;
	char		**new_cmd;

	list = NULL;
	expand_one_node(node->cmd, env, &list);
	new_cmd = cpy_list_to_cmd(list);
	list_free_all(&list);
	free_double_pointer(node->cmd);
	node->cmd = new_cmd;
	return ;
}
