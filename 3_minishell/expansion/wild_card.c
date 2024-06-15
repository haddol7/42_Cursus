/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:07:51 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/16 07:12:02 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int	is_all_star(char *f_name)
{
	int	i;

	i = 0;
	while (f_name[i] != '\0')
	{
		if (f_name[i] != '*')
			return (0);
		i++;
	}
	return (1);
}

void	fill_table(int **table, char *pattern, int t, int p)
{
	int	i;
	int	j;

	j = 1;
	while (pattern[j - 1] == '*')
	{
		table[0][j] = 1;
		j++;
	}
	while(j <= p)
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

void	print_table(int **table, int t, int p)//TODO 지워
{
	int	i;
	int j;

	i = 0;
	j = 0;

	while (i <= t)
	{
		j = 0;
		while (j <= p)
		{
			printf("%d  ", table[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
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

void	calculate_table(int **table, char *text, char *pattern)
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
			if (text[i - 1] == pattern[j - 1])
				table[i][j] = table[i - 1][j - 1];
			else if (pattern[j - 1] == '*')
			{
				if (table[i - 1][j] == 1 || table[i][j - 1] == 1)
					table[i][j] = 1;
				else
					table[i][j] = 0;
			}
		}
	}
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

t_new_cmd	*expand_wild_card(t_new_cmd *node)
{
	char 			path[256];
	DIR				*p_dir;
	struct dirent	*dir_ent;
	t_new_cmd		*sub_list;

	sub_list = NULL;
	delete_quote(node);
	ft_memset(path, 0, 256);
	getcwd(path, 256);
	p_dir = opendir(path);
	while (1)
	{
		dir_ent = readdir(p_dir);
		if (dir_ent == NULL)
			break ;
		if (node->cmd[0] != '.' && dir_ent->d_name[0] == '.')
			continue ;
		if (is_match_cmd(dir_ent->d_name, node->cmd) == 1)
			cmd_add_back(&sub_list, ft_strdup(dir_ent->d_name));
	}
	closedir(p_dir);
	return (sub_list);
}

t_new_cmd *check_one_cmd(t_new_cmd *node)
{
	int			i;
	int			quote;
	t_new_cmd	*sub_list;

	i = 0;
	quote = 0;
	sub_list = NULL;
	while (node->cmd[i] != '\0')
	{
		quote_lock(node->cmd[i], &quote);
		if (quote == 0 && node->cmd[i] == '*')
		{
			sub_list = expand_wild_card(node);
			break ;
		}
		i++;
	}
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