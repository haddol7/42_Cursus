/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:15:23 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/17 17:48:00 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"
# include <dirent.h>
typedef struct s_env
{
	char			*key;
	char			*value;
	int				complete;
	struct s_env	*next;
}	t_env;

typedef struct s_new_cmd
{
	char				*cmd;
	struct s_new_cmd	*next;
}	t_new_cmd;

typedef struct s_wild_card
{
	int	*idx_list;
	int	len;
}	t_wild_card;

void		quote_lock(char c, int *status);
void		expand_dollar(char *cmd, t_env *env, t_new_cmd **list);
char		*ms_strcpy(int start, int end, char *str);
t_env		*env_cpy(char **envp);
int			env_strncmp(char *s1, char *name, int n);
t_env		*env_new(char *name, char *content);
t_env		*env_last(t_env *head);
void		env_add_back(t_env **head, t_env *new);
int			env_free_all(t_env **head);
int			ms_strlen(char *str);
char		*ms_strjoin(char *s1, char *s2);
void		free_all_old_cmd(char **cmd);
void		expansion(t_node *ast, t_env *env);
char		**cpy_list_to_cmd(t_new_cmd *new_list);
int			get_cmd_node_num(t_new_cmd *head);
int			list_free_all(t_new_cmd **head);
void		cmd_add_back(t_new_cmd **head, char *new);
t_new_cmd	*cmd_last(t_new_cmd *head);
t_new_cmd	*cmd_new(char *cmd);
void		expand_quote(t_new_cmd *list, t_env *env);
char		*exit_status(void);
char	*de_quote(char *cmd, int *idx, char *words_tmp, char quote);\
char	*no_quote(char *cmd, int *idx, char *words_tmp);
void	del_one_cmd(t_new_cmd **head, t_new_cmd **node);
t_new_cmd	*join_sub_cmd(t_new_cmd **head, t_new_cmd *node, t_new_cmd *sub_list);
// void	print_all_env(t_env *head); //TODO ㅈㅣ우ㅓㅜ
void		print_all_cmd(t_new_cmd *head);

int	is_all_star(char *pattern);

void	wild_card(t_new_cmd **head);
void	free_table(int **table, int	t);
int	is_match_cmd(char *text, char *pattern, t_wild_card star_list);
void	delete_quote(t_new_cmd *node);
void	fill_table(int **table, char *pattern, int t, t_wild_card star_list);
void	calculate_table(int **table, char *text, char *pattern, t_wild_card star_list);
t_new_cmd	*expand_wild_card(t_new_cmd *node, t_wild_card star_list);
t_new_cmd *check_one_cmd(t_new_cmd *node);
void	wild_card(t_new_cmd **head);
void    check_star_idx(char *cmd, t_wild_card *list);
int	is_in_star_list(t_wild_card star_list, int idx);
int	**init_table(int t, int p, char *pattern, t_wild_card star_list);
// int is_hidden_file(t_new_cmd *node, char *d_name);
#endif
