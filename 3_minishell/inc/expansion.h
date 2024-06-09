/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:15:23 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/09 19:20:35 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "parser.h"
# include "tokenizer.h"

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
void	check_cmd_node(t_node *ast, t_env *env);
void	env_cpy(t_env **env, char **envp);
char	*env_strcpy(int start, int end, char *str);
int		env_strncmp(char *s1, char *name, int n);
int		is_alpha_num(char *var);
char	*ms_strjoin(char *s1, char *s2);
t_new_cmd	*cmd_new(char *cmd);
t_new_cmd	*cmd_last(t_new_cmd *head);
void	cmd_add_back(t_new_cmd **head, char *new);
int	list_free_all(t_new_cmd **head);
int	get_cmd_node_num(t_new_cmd *head);

void	print_all_env(t_env *head); //TODO ㅈㅣ우ㅓㅜ
void	print_all_cmd(t_new_cmd *head);
#endif
