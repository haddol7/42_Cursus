/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:10:14 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/18 17:33:52 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

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

char	*return_value(char *dollar_start, t_env *env)
{
	int		i;
	char	*value;
	int		key_len;

	i = 1;
	key_len = 0;
	value = NULL;
	if (dollar_start[i] == '?')
		return (exit_status());
	if (ft_isalnum(dollar_start[i]) == 0)
		return (0);
	while (ft_isalnum(dollar_start[i]) || dollar_start[i] == '_')
		i++;
	key_len = i - 1;
	while (env != NULL)
	{
		if (env_strncmp(dollar_start + 1, env->key, i - 1) == 0)
		{
			if (env->complete == 0)
				break ;
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*replace_cmd(char *origin, char **value, int *dollar_idx)
{
	char	*part1;
	char	*part2;
	char	*result;
	char	*tmp;
	int		del_len;

	del_len = 1;
	while (ft_isalnum(*(origin + *dollar_idx + del_len)) || \
			*(origin + *dollar_idx + del_len) == '_')
		del_len++;
	if (del_len == 1 && origin[*dollar_idx + del_len])
		del_len = 2;
	part1 = ms_strcpy(0, *dollar_idx, origin);
	tmp = ft_strjoin(part1, *value);
	part2 = ms_strcpy(*dollar_idx + del_len, ms_strlen(origin), origin);
	result = ft_strjoin(tmp, part2);
	*dollar_idx = ms_strlen(tmp) - 1;
	free(tmp);
	free(part1);
	free(part2);
	free(origin);
	free(*value);
	*value = NULL;
	return (result);
}

void	add_list(t_new_cmd **list, char *new_cmd)
{
	int		i;
	int		start;
	int		quote;
	char	*split;

	i = 0;
	start = 0;
	quote = 0;
	while (new_cmd != NULL && new_cmd[i] != '\0')
	{
		quote_lock(new_cmd[i], &quote);
		if (quote == 0 && new_cmd[i] == ' ')
		{
			split = ms_strcpy(start, i, new_cmd);
			cmd_add_back(list, split);
			while (new_cmd[i] == ' ')
				i++;
			start = i;
			continue ;
		}
		else
			i++;
	}
	split = ms_strcpy(start, i, new_cmd);
	cmd_add_back(list, split);
}

void	expand_dollar(char *cmd, t_env *env, t_new_cmd **list)
{
	int		j;
	int		quote;
	char	*expand_value;
	char	*new_cmd;

	j = 0;
	quote = 0;
	new_cmd = ft_strdup(cmd);
	while (new_cmd != NULL && new_cmd[j] != '\0')
	{
		quote_lock(new_cmd[j], &quote);
		if (new_cmd[j] == '$' && quote != 1)
		{
			expand_value = return_value(new_cmd + j, env);
			if (expand_value != NULL)
				new_cmd = replace_cmd(new_cmd, &expand_value, &j);
		}
		j++;
	}
	if (new_cmd != NULL && new_cmd[0] == '\0')
		new_cmd = cmd_to_null(new_cmd);
	else
		add_list(list, new_cmd);
	if (new_cmd != NULL)
		free(new_cmd);
}
