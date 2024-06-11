/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:30:41 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/11 20:03:12 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

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
	str = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
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

void	free_all_old_cmd(char **cmd)
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

char	*replace_str(char *cmd, int start, int end, char *value)
{
	char	*tmp;
	char	*result1;
	char	*result2;

	printf("cmd :: %s start :: %d end ::: %d\n", cmd, start, end);
	
	printf("🎨🎨🎨 : %s\n",cmd);
	tmp = ms_strcpy(0, start, cmd);
	
	printf("tmp ::: %s\n", tmp);
	
	result1 = ft_strjoin(tmp, value);
	if (result1 == NULL)
		handle_error("exit : malloc error1", 1, 0);
	free(tmp);
	tmp = ms_strcpy(end + 1, ms_strlen(cmd), cmd);
	printf("tmp ::: %s\n", tmp);
	result2 = ft_strjoin(result1, tmp);
	free(result1);
	free(tmp);
	// if (quote != 0)
	// {
	// 	result2 = ft_strjoin(result1, "\"");
	// 	if (result2 == NULL)
	// 		handle_error("exit : malloc error", 1, 0);
	// 	free(result1);
	// 	return (result2);
	// }
	return (result2);
}