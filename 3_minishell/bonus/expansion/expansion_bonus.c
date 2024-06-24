/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:07:27 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/25 04:35:09 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_bonus.h"
#include "execution_bonus.h"

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
	expand_quote(*list);
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
	result = (char **)ft_malloc(sizeof(char *) * (word_cnt + 1));
	i = 0;
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

char	*env_join_key_value(char *key, char *value)
{
	char	*temp;
	char	*str;

	if (value == NULL)
		return (key);
	temp = ft_strjoin(key, "=");
	str = ft_strjoin(temp, value);
	free(temp);
	return (str);
}
