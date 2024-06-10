/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:10:14 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/10 18:38:49 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	quote_lock(char c, int *status);
void	ms_split(char *str, t_new_cmd **list);
void	find_dollar_and_expand(char *cmd, t_env *env, char **str);
char	*replace_env(char *cmd, int idx, t_env *env, int quote);
int		is_exception(char *cmd, int idx);

int	is_exception(char *cmd, int idx)
{
	if (cmd[idx + 1] == '\"' || \
				cmd[idx + 1] == '\0' || cmd[idx + 1] == '$')
		return (1);
	return (0);
}

void	quote_lock(char c, int *status)
{
	if (*status == 0)
	{
		if (c == '\'')
			*status = 1;
		if (c == '\"')
			*status = 2;
	}
	else if (*status == 1)
	{
		if (c == '\'')
			*status = 0;
	}
	else if (*status == 2)
	{
		if (c == '\"')
			*status = 0;
	}
}

void	ms_split(char *str, t_new_cmd **list)
{
	int	i;
	int	start;
	char	*tmp;
	int	quote_status;

	i = 0;
	start = 0;
	quote_status = 0;
	while (str != NULL)
	{
		quote_lock(str[i], &quote_status);
		if (quote_status == 0 && str[i] == ' ')
		{
			cmd_add_back(list, env_strcpy(start, i - 1, str));
			// cmd_add_back(list, ft_strdup(" "));//TODO 일단 공백 1개만 포함.
			while (str[i] == ' ')
				i++;
			start = i;
		}
		if (str[i] == '\0')
		{
			cmd_add_back(list, env_strcpy(start, i - 1, str));//TODO 요부분
			break ;
		}
		i++;
	}
}

void	find_dollar_and_expand(char *cmd, t_env *env, char **str)
{
	int		i;
	int		quote_status;
	int		key_len;

	quote_status = 0;
	key_len = 0;
	i = 0;
	while (cmd != NULL && cmd[i] != '\0')
	{
		// printf("AERA??");
		printf("cmd[i] ::: %c\n", cmd[i]);
		quote_lock(cmd[i], &quote_status);
		if ((cmd[i] == '$') && is_exception(cmd, i) == 0 && \
			quote_status != 1)
		{
			free(*str);
			*str = replace_env(cmd, i, env, quote_status);
		}
		i++;
	}
}

char	*replace_env(char *cmd, int idx, t_env *env, int quote)
{
	int	start;
	int	end;
	char	*expand;

	start = idx++;
	expand = NULL;
	while (ft_isalnum(*(cmd + idx)) || cmd[idx] == '_')
		idx++;
	end = idx - 1;
	// *idx = end - start + 1;// TODO 이렇게 하면 부모함수에서 j++ 해줘야 함.
	while (env != NULL)
	{
		if (env_strncmp(cmd + start + 1, env->key, end - start) == 0)
		{
			expand = replace_str(cmd, start, env->value, quote);
			break ;
		}
		env = env->next;
	}
	if (expand == NULL)
		expand = replace_str(cmd, start, "", quote);
	return (expand);
}
