/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:41:57 by daeha             #+#    #+#             */
/*   Updated: 2024/06/15 21:26:04 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execution.h"

static char *get_key_or_value(char **str, char delim);

void	ms_export(char **arg, t_env *env)
{
	t_bool	error;
	t_env	*temp_env;
	char	*key;
	char	*value;
	
	arg++;
	error = FALSE;
	// if (*arg == NULL)
	// 	display_declare_list(env);
	while (*arg)
	{
		if (is_env_key_valid(*arg))
		{
			key = get_key_or_value(&(*arg), KEY);
			value = get_key_or_value(&(*arg), VALUE);
			temp_env = env_find_pointer(key, env);
			if (temp_env == NULL)
			{
				temp_env = env_new(key, value);
				if (value == NULL)
					temp_env->complete = 0;
				env_add_back(&env, temp_env);
			}
			else if (value != NULL) 
			{
				temp_env->complete = 1;
				if (temp_env->value != NULL)
					free(temp_env->value);
				temp_env->value = value;
				free(key);
			}
		}
		else
			error = TRUE;
		arg++;
	}
	if (error)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

static char *get_key_or_value(char **str, char delim)
{
	char	*key;
	size_t	len;

	len = 0;
	if (!(*str)[len])
		return (NULL);
	while ((*str)[len] && (*str)[len] != delim)
		len++;
	key = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(key, *str, len + 1);
	*str += len;
	if (delim == KEY && **str != '\0')
		(*str)++;
	return (key);
}

t_bool	is_env_key_valid(char *str)
{
	size_t	i;
	
	i = 0;
	if (str[i] != '_' && !ft_isalpha(str[i++]))
	{
		error_cmd_exit(str, EVALUE);
		return (FALSE);
	}
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && !ft_isalnum(str[i++]))
		{
			error_cmd_exit(str, EVALUE);
			return (FALSE);
		}
	}
	return (TRUE);
}
