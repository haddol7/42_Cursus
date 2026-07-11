/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:07:51 by jungslee          #+#    #+#             */
/*   Updated: 2024/07/02 17:38:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_bonus.h"

void	fill_table(int **table, char *pattern, int t, t_wild_card star_list)
{
	int	i;
	int	j;

	j = 1;
	while (pattern[j - 1] == '*' && is_in_star_list(star_list, j - 1))
	{
		table[0][j] = 1;
		j++;
	}
	while (j <= ms_strlen(pattern))
	{
		table[0][j] = 0;
		j++;
	}
	i = 1;
	while (i <= t)
	{
		table[i][0] = 0;
		i++;
	}
}

void	calculate_table(int **table, char *text, char *pattern, \
						t_wild_card star_list)
{
	int	i;
	int	j;
	int	t_len;
	int	p_len;

	t_len = ms_strlen(text);
	p_len = ms_strlen(pattern);
	i = 0;
	while (++i <= t_len)
	{
		j = 0;
		while (++j <= p_len)
		{
			table[i][j] = 0;
			if (pattern[j - 1] == '*' && is_in_star_list(star_list, j - 1))
			{
				if (table[i - 1][j] == 1 || table[i][j - 1] == 1)
					table[i][j] = 1;
				else
					table[i][j] = 0;
			}
			else if (text[i - 1] == pattern[j - 1])
				table[i][j] = table[i - 1][j - 1];
		}
	}
}

t_new_cmd	*expand_wild_card(t_new_cmd *node, t_wild_card star_list)
{
	char			path[256];
	DIR				*p_dir;
	struct dirent	*dir_ent;
	t_new_cmd		*sub_list;

	sub_list = NULL;
	delete_quote(node);
	ft_memset(path, 0, 256);
	getcwd(path, 256);
	p_dir = opendir(path);
	while (p_dir != NULL)
	{
		dir_ent = readdir(p_dir);
		if (dir_ent == NULL)
			break ;
		if (node->cmd[0] != '.' && dir_ent->d_name[0] == '.')
			continue ;
		if (ms_strlen(node->cmd) == star_list.len || \
			is_match_cmd(dir_ent->d_name, node->cmd, star_list) == 1)
			cmd_add_back(&sub_list, ft_strdup(dir_ent->d_name));
	}
	if (p_dir != NULL)
		closedir(p_dir);
	return (sub_list);
}

t_new_cmd	*check_one_cmd(t_new_cmd *node)
{
	int			i;
	int			quote;
	t_new_cmd	*sub_list;
	t_wild_card	star_list;

	i = 0;
	quote = 0;
	sub_list = NULL;
	check_star_idx(node->cmd, &star_list);
	while (node->cmd[i] != '\0')
	{
		quote_lock(node->cmd[i], &quote);
		if (quote == 0 && node->cmd[i] == '*')
		{
			sub_list = expand_wild_card(node, star_list);
			break ;
		}
		i++;
	}
	if (star_list.idx_list != NULL)
		free(star_list.idx_list);
	return (sub_list);
}

void	wild_card(t_new_cmd **head)
{
	t_new_cmd	*tmp;
	t_new_cmd	*now;
	t_new_cmd	*sub_list;

	sub_list = NULL;
	now = *head;
	while (now != NULL)
	{
		sub_list = check_one_cmd(now);
		if (sub_list != NULL)
		{
			tmp = now;
			now = join_sub_cmd(head, now, sub_list);
			del_one_cmd(head, &tmp);
		}
		else
			now = now->next;
	}
}
