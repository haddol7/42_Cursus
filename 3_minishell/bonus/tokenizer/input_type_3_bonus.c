/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_type_3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:19:42 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/25 04:35:09 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	check_if_terminal(char c1, char c2)
{
	if (c1 != '\0' && \
		c1 != ' ' && c1 != '|' && \
		c1 != '<' && c1 != '>' && \
		c1 != '(' && c1 != ')' && \
		!(c1 == '&' && c2 == '&') && \
		!(c1 == '|' && c2 == '|')
	)
		return (0);
	else
		return (1);
}

int	skip_quote(char *input, int idx)
{
	char	quote;
	int		i;

	i = 1;
	quote = input[idx];
	while (input[idx + i] != quote)
	{
		if (input[idx + i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}

int	word_len(char *input, int start, int in_quote)
{
	int	len;

	len = 0;
	while (input[start + len] != '\0')
	{
		if (input[start + len] == '\'' || input[start + len] == '\"')
		{
			in_quote = skip_quote(input, start + len);
			if (in_quote == -1)
				return (-1);
			len += in_quote;
		}
		if (check_if_terminal(input[start + len], input[start + len + 1]) == 1)
			break ;
		len++;
	}
	return (len);
}

int	input_word(t_token **head, char *input, int *idx)
{
	t_token	*node;
	char	*value;
	int		len;
	int		start;
	int		in_quote;

	start = *idx;
	in_quote = 0;
	len = word_len(input, start, in_quote);
	if (len == -1)
		return (handle_error(ERR_TOK, 0, head));
	value = (char *)ft_malloc(sizeof(char) * (len + 1));
	ft_strlcpy(value, (const char *)(input + start), len + 1);
	node = ms_lstnew(value, T_WORD);
	ms_lstadd_back(head, node);
	*idx = start + len;
	return (1);
}
