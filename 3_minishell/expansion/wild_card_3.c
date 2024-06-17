/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:47:06 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/17 17:31:16 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	init_star_list(t_wild_card *list)
// {
// 	list->len = 0;
// 	list->idx_list = NULL;
// }

void	init_and_cnt_star(char *cmd, t_wild_card *list)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	list->len = 0;
	list->idx_list = 0;
	while (cmd[i] != '\0')
	{
		quote_lock(cmd[i], &quote);
		if(cmd[i] == '*' && quote == 0)
			list->len++;
		i++;
	}
	list->idx_list = (int *)malloc(sizeof(int) * list->len);
}

void    check_star_idx(char *cmd, t_wild_card *list)
{
	int	i;
	int	j;
	int	quote;
	int	pre_quote;
	int	quote_cnt;

	i = 0;
	j = 0;
	quote = 0;
	quote_cnt = 0;
	pre_quote = quote;
	init_and_cnt_star(cmd, list);
	while (cmd[i] != '\0')
	{
		quote_lock(cmd[i], &quote);
		if (pre_quote != quote)
			quote_cnt++;
		pre_quote = quote;
		if (quote == 0 && cmd[i] == '*')
		{
			(list->idx_list)[j] = i - quote_cnt;
			j++;
		}
		i++;
	}
}

int	is_in_star_list(t_wild_card star_list, int idx)
{
	int	i;

	i = 0;
	while (i < star_list.len)
	{
		if (idx == star_list.idx_list[i])
			return (1);
		i++;
	}
	return (0);
}

// int is_hidden_file(t_new_cmd *node, char *d_name)
// {
//     int i;

//     i = 0;
//     while (node->cmd[i] == '\'' || node->cmd[i] == '\"' || \
//             node->cmd[i] == ' ')
//         i++;
//     if (node->cmd[i] != '.' && d_name[0] == '.')
//         return (1);
//     return (0);
// }
