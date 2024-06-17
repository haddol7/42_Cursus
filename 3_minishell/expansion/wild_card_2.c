/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:29:59 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/17 16:34:50 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_star(char *pattern)
{
	int	i;

	i = 0;
	while (pattern[i] != '\0')
	{
		if (pattern[i] != '*')
			return (0);
		i++;
	}
	return (1);
}

int	**init_table(int t, int p, char *pattern)
{
	int	**table;
	int	i;
	int	j;

	i = 0;
	table = (int **)malloc((sizeof(int *)) * (t + 1));
	while (i <= t)
	{
		table[i] = (int *)malloc((sizeof(int)) * (p + 1));
		i++;
	}
	table[0][0] = 1;
	fill_table(table, pattern, t, p);
	return (table);
}

void	free_table(int **table, int	t)
{
	int	i;

	i = 0;
	while (i < t + 1)
	{
		free(table[i]);
		i++;
	}
	free(table);
}

int	is_match_cmd(char *text, char *pattern)
{
	int	pattern_len;
	int	text_len;
	int	**table;
	int	ret;

	text_len = ms_strlen(text);
	pattern_len = ms_strlen(pattern);
	if (is_all_star(pattern))
		return (1);
	table = init_table(text_len, pattern_len, pattern);
	calculate_table(table, text, pattern);
	ret = table[text_len][pattern_len];
	free_table(table, text_len);
	return (ret);	
}

void	delete_quote(t_new_cmd *node)
{
	int		i;
	char	*word_tmp;

	i = 0;
	word_tmp = NULL;
	while (node->cmd[i] != '\0')
	{
		if (node->cmd[i] ==  '\'' || node->cmd[i] == '\"')
			word_tmp = de_quote(node->cmd, &i, word_tmp, node->cmd[i]);
		else
			word_tmp = no_quote(node->cmd, &i, word_tmp);
	}
	free(node->cmd);
	node->cmd = word_tmp;
}