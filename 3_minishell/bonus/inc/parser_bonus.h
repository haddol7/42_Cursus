/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:54:45 by daeha             #+#    #+#             */
/*   Updated: 2024/06/19 23:39:09 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_BONUS_H
# define PARSER_BONUS_H

# include "tokenizer_bonus.h"
# include "libft.h"

# define SYNTAX_ERR 2
# define SYNTAX_MSG "minishell: syntax error near unexpected token `newline'"

typedef enum e_node_type
{
	N_CMD,
	N_AND,
	N_OR,
	N_PIPE,
	N_SUBSHELL,
	N_INPUT,
	N_OUTPUT,
	N_HERE_DOC,
	N_APPEND
}	t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char			**cmd;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

//parser.c
t_node	*parser(t_token *token);
void	*free_all_tree(t_node **node);
void	*free_arg(char ***cmd);
t_bool	*get_parser_error(void);
void	set_parser_error(t_bool is_error);

//p_grammer.c
t_node	*list(t_token **token);
t_node	*pipeline(t_token **token);
t_node	*command(t_token **token);
t_node	*subshell(t_token **token);
t_node	*simple_command(t_token **token);

//p_grammer_2.c
t_node	*redirect_list(t_token **token);
t_node	*io_redirect(t_token **token);

//p_utils.c
t_node	*new_parent_node(t_node_type type, t_node *left, t_node *right);
t_node	*new_cmd_node(t_node_type type, char **arg);
t_node	*link_redir_to_node(t_node *node, t_node *redir);
t_node	*append_redir_node(t_node *redir, t_token **token);
char	**append_cmd_arg(char **arg, t_token **token);

//p_utils_2.c
void	*free_simple_command(char **arg, t_node *node);
t_bool	is_token_redir(t_token *token);
t_bool	is_token(t_token *token, t_token_type type);
void	token_next(t_token **token);

//p_syntax_error.c
void	*syntax_error(t_token *token);
#endif
