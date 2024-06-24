/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:41:57 by daeha             #+#    #+#             */
/*   Updated: 2024/06/25 04:37:33 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"
#include "execution_bonus.h"
#include "minishell_bonus.h"

static void		env_export(char *arg, t_env *env);
static char		*get_key_or_value(char *str, char type);
static void		set_env_info(char *key, char *value, t_env *env);
static t_bool	is_env_key_valid(char *str);

void	ms_export(char **arg, t_env *env)
{
	t_bool	error;

	arg++;
	error = FALSE;
	if (*arg == NULL)
		display_declare_list(env);
	while (*arg)
	{
		if (is_env_key_valid(*arg))
			env_export(*arg, env);
		else
			error = TRUE;
		arg++;
	}
	if (error)
		set_status(EXIT_FAILURE);
	else
		set_status(EXIT_SUCCESS);
}

static t_bool	is_env_key_valid(char *str)
{
	size_t	i;

	i = 1;
	if (str[0] != '_' && !ft_isalpha(str[0]))
	{
		error_cmd_exit(str, EVALUE);
		return (FALSE);
	}
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
		{
			error_cmd_exit(str, EVALUE);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

static void	env_export(char *arg, t_env *env)
{
	t_env	*temp_env;
	char	*key;
	char	*value;

	key = get_key_or_value(arg, KEY);
	value = get_key_or_value(arg, VALUE);
	temp_env = env_find_pointer(key, env);
	if (!temp_env && env->key == NULL)
		set_env_info(key, value, env);
	else if (!temp_env)
		env_add_back(&env, env_new(key, value));
	else if (value != NULL)
	{
		temp_env->complete = 1;
		if (temp_env->value != NULL)
			free(temp_env->value);
		temp_env->value = value;
		free(key);
	}
	else
		free(key);
}

static char	*get_key_or_value(char *str, char type)
{
	char	*content;
	size_t	len;

	len = 0;
	if (!str[0])
		return (NULL);
	if (type == VALUE)
	{
		while (*str && *str != '=')
			str++;
		if (*str == '=')
		{
			str++;
			if (!*str)
				return (ft_strdup(""));
		}
		else
			return (NULL);
	}
	while (str[len] && str[len] != type)
		len++;
	content = ft_malloc(sizeof(char) * (len + 1));
	ft_strlcpy(content, str, len + 1);
	return (content);
}

static void	set_env_info(char *key, char *value, t_env *env)
{
	env->key = key;
	env->value = value;
	env->complete = 0;
	if (value != NULL)
		env->complete = 1;
}
