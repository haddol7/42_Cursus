/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:55:55 by daeha             #+#    #+#             */
/*   Updated: 2024/05/25 19:51:23 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

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
	T_ERROR
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

t_token	*tokenizer(char *input);

#endif
