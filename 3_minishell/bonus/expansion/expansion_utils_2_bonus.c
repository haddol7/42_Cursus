/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:30:41 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/19 23:21:16 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_bonus.h"
#include "execution_bonus.h"

int	ms_strlen(char *str)
{
	int	cnt;

	cnt = 0;
	while (str != NULL && str[cnt] != '\0')
		cnt++;
	return (cnt);
}

char	*ms_strjoin(char *s1, char *s2)
{
	char	*str;
	int		idx;
	int		s1_len;
	int		s2_len;

	idx = 0;
	s1_len = ms_strlen(s1);
	s2_len = ms_strlen(s2);
	str = (char *)ft_malloc((s1_len + s2_len + 1) * sizeof(char));
	if (str == NULL)
		handle_error("exit : malloc error", 1, 0);
	while (idx < s1_len)
	{
		str[idx] = s1[idx];
		idx++;
	}
	while (idx < s1_len + s2_len)
	{
		str[idx] = s2[idx - s1_len];
		idx++;
	}
	str[idx] = '\0';
	return (str);
}

void	free_double_pointer(char **cmd)
{
	int	i;

	i = 0;
	while (cmd != NULL && cmd[i] != NULL)
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	env_update_shlvl(t_env **env)
{
	int		level;
	t_env	*shlvl;

	level = 1;
	shlvl = env_find_pointer("SHLVL", *env);
	if (shlvl == NULL)
	{
		env_add_back(env, env_new(ft_strdup("SHLVL"), ft_strdup("1")));
		return ;
	}
	if (shlvl->value != NULL)
	{
		level = ft_atoi(shlvl->value) + 1;
		free(shlvl->value);
	}
	if (level <= 0)
		level = 1;
	shlvl->value = ft_itoa(level);
	shlvl->complete = 1;
}
