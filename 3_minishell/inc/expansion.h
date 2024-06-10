/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:15:23 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/10 20:44:10 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"
// # include "parser.h"
// # include "tokenizer.h"

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

t_env	*env_new(char *name, char *content);
t_env	*env_last(t_env *head);
void	env_add_back(t_env **head, t_env *new);
int		env_free_all(t_env **head);
void	expansion(t_node *ast, t_env *env);
t_env *env_cpy(char **envp);
char	*env_strcpy(int start, int end, char *str);
int		env_strncmp(char *s1, char *name, int n);
int		is_alpha_num(char *var);
t_new_cmd	*cmd_new(char *cmd);
t_new_cmd	*cmd_last(t_new_cmd *head);
void	cmd_add_back(t_new_cmd **head, char *new);
int	list_free_all(t_new_cmd **head);
int	get_cmd_node_num(t_new_cmd *head);
char	*ms_strjoin(char *s1, char *s2);
int	ms_strlen(char *str);
void	free_all_old_cmd(char **cmd);
void	handle_quote(t_new_cmd *list, t_env *env);
char	*no_quote(char *cmd, int *idx, char *words_tmp);
char	*replace_str(char *cmd, int start, int end, char *value);

void	quote_lock(char c, int *status);
void	ms_split(char *str, t_new_cmd **list);
// char	*replace_env(char *cmd, int *idx, t_env *env, int quote);
int		is_exception(char *cmd, int idx);

char	*env_validity(char *cmd, int idx, t_env *env, int *key_len);
void	check_env_and_expand(t_node *node, t_env *env, t_new_cmd **list);
char	**cpy_list_to_cmd(t_new_cmd *new_list);
char	*find_dollar_and_expand(char *cmd, t_env *env);
char	*replace_env(char *cmd, int *idx, t_env *env, int quote);


// void	print_all_env(t_env *head); //TODO ㅈㅣ우ㅓㅜ
void	print_all_cmd(t_new_cmd *head);
#endif
