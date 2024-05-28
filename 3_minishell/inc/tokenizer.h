/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:55:55 by daeha             #+#    #+#             */
/*   Updated: 2024/05/28 16:54:06 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_DLESS,
	T_DGREAT,
	T_LESS,
	T_GREAT,
	T_LPAREN,
	T_RPAREN,
	T_AND_IF,
	T_OR_IF,
	T_ERROR,
	T_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

t_token	*tokenizer(char *input);
t_token	*ms_lstnew(char *value, t_token_type type);
t_token	*ms_lstlast(t_token *head);
void	ms_lstadd_back(t_token **head, t_token *new);
int		input_quotation(t_token **head, char *input, int *idx);
void	input_pipe(t_token **head, int *idx);
void	input_redirection(t_token **head, char *input, int *idx);
void	input_paren(t_token **head, char input, int *idx);
void	input_and_if(t_token **head, int *idx);
void	input_or_if(t_token **head, int *idx);
int		input_word(t_token **head, char *input, int *idx);
int		ms_free_all_token(t_token **head);
void	eof_node(t_token **head);
int		handle_error(char *str, int code, t_token **head);

void	print_all_value(t_token *head);//TODO 지워

#endif
