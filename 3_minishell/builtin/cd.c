/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:32:23 by daeha             #+#    #+#             */
/*   Updated: 2024/06/18 16:39:50 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	error_enoent(char *arg);
static char	*get_absolute_path(char *arg, t_bool *malloc);
static void	env_update_pwd(t_env *env);
static void	env_update_oldpwd(t_env *env, char *old_pwd);

void	ms_cd(char **arg, t_env *env)
{
	t_bool	target_malloc;
	char	*target;
	char	*file;

	file = arg[1];
	target_malloc = FALSE;
	if (!file || !ft_strcmp(file, "~"))
		target = env_find_value("HOME", env);
	else if (*file != '.' && *file != '/')
		target = get_absolute_path(file, &target_malloc);
	else
		target = file;
	if (chdir(target) == -1)
	{
		error_enoent(file);
		return ;
	}
	if (target_malloc)
		free(target);
	env_update_pwd(env);
	g_status = EXIT_SUCCESS;
}

static void	env_update_pwd(t_env *env)
{
	t_env	*node;
	char	*old_pwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	node = env_find_pointer("PWD", env);
	if (node == NULL)
	{	
		env_add_back(&env, env_new(ft_strdup("PWD"), pwd));
		old_pwd = NULL;
	}
	else
	{
		old_pwd = node->value;
		node->value = pwd;
	}
	env_update_oldpwd(env, old_pwd);
}

static void	env_update_oldpwd(t_env *env, char *old_pwd)
{
	t_env	*node;

	node = env_find_pointer("OLDPWD", env);
	if (node == NULL)
		env_add_back(&env, env_new(ft_strdup("OLDPWD"), old_pwd));
	else
	{	
		node->complete = 1;
		if (node->value)
			free(node->value);
		node->value = old_pwd;
		if (!old_pwd)
			node->complete = 0;
	}
}

static void	error_enoent(char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(ENOENT), STDERR_FILENO);
	g_status = EXIT_FAILURE;
}

static char	*get_absolute_path(char *arg, t_bool *malloc)
{
	char	*target;
	char	*temp;

	target = getcwd(NULL, 0);
	temp = ft_strjoin(target, "/");
	free(target);
	target = ft_strjoin(temp, arg);
	free(temp);
	*malloc = TRUE;
	return (target);
}
