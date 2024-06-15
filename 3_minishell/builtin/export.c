/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:41:57 by daeha             #+#    #+#             */
/*   Updated: 2024/06/16 04:26:29 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execution.h"

extern int g_status;

static void env_export(char *arg, t_env *env);
static char *get_key_or_value(char *str, char type);

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
		g_status = EXIT_FAILURE;
	g_status = EXIT_SUCCESS;
}

t_bool	is_env_key_valid(char *str)
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
		if (str[i] != '_' && !ft_isalnum(str[i++]))
		{
			error_cmd_exit(str, EVALUE);
			return (FALSE);
		}
	}
	return (TRUE);
}

static void env_export(char *arg, t_env *env)
{
	t_env	*temp_env;
	char	*key;
	char	*value;

	key = get_key_or_value(arg, KEY);
	value = get_key_or_value(arg, VALUE);
	temp_env = env_find_pointer(key, env);
	if (!temp_env && env->key == NULL)
	{
		env->key = key;
		env->value = value;
		env->complete = 0;
		if (value != NULL)
			env->complete = 1;
	}
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
}

static char *get_key_or_value(char *str, char type)
{
	char	*key;
	size_t	len;

	len = 0;
	if (!str[0])
		return (NULL);
	if (type == VALUE)
	{
		while (*str && *str != '=')
			str++;
		if (*str)
			str++;
	}
	while (str[len] && str[len] != type)
		len++;
	key = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(key, str, len + 1);
	if (type == KEY && str[len] != '\0')
		len++;
	return (key);
}
