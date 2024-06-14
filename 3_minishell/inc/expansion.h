/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:15:23 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/14 22:27:54 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>
# include "parser.h"
# include "libft.h"

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
void		free_double_pointer(char **cmd);
void		expansion(t_node *ast, t_env *env);
char		**cpy_list_to_cmd(t_new_cmd *new_list);
int			get_cmd_node_num(t_new_cmd *head);
int			list_free_all(t_new_cmd **head);
void		cmd_add_back(t_new_cmd **head, char *new);
t_new_cmd	*cmd_last(t_new_cmd *head);
t_new_cmd	*cmd_new(char *cmd);
void		expand_quote(t_new_cmd *list);
char	**env_join(t_env *ms_envp);
char *env_join_key_value(char *key, char *value);

#endif
