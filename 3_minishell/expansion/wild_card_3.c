/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:47:06 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/17 17:04:54 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    check_star_idx(char *cmd, t_wild_card *list)
{
	int	len;
	int	i;
	int	j;
	int	quote;

	i = 0;
	len = 0;
	while (cmd[i] != '\0')
	{
		quote_lock(cmd[i], &quote);
		if (cmd[i++] == '*' && quote == 0)
			len++;
	}
	list->idx_list = (int *)malloc(sizeof(int) * len);	
	i = 0;
	j = 0;
	quote = 0;
	while (cmd[i] != '\0')
	{
		quote_lock(cmd[i], &quote);
		if (quote == 0 && cmd[i] == '*')
			(list->idx_list)[j++] = i;
		i++;
	}
	list->len = len;
}
