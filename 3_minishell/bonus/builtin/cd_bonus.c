/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:32:23 by daeha             #+#    #+#             */
/*   Updated: 2024/07/02 17:38:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"
#include "expansion_bonus.h"
#include "execution_bonus.h"
#include "minishell_bonus.h"

static char	*get_path(char **arg, t_env *env, t_bool *target_malloc);
static char	*get_absolute_path(char *arg, t_bool *malloc);
static int	check_valid_path(t_env *env);

int	ms_cd(char **arg, t_env *env)
{
	t_bool	target_malloc;
	char	*target;
	char	*old_pwd;

	target = get_path(arg, env, &target_malloc);
	if (target == NULL)
		return (0);
	if (chdir(target) == -1)
		return (error_cd_enoent(arg[1], target, target_malloc));
	check_valid_path(env);
	if (target_malloc)
		free(target);
	old_pwd = env_update_pwd(&env);
	env_update_oldpwd(&env, old_pwd);
	set_status(EXIT_SUCCESS);
	return (0);
}

static char	*get_path(char **arg, t_env *env, t_bool *target_malloc)
{	
	char	*target;
	char	*file;

	*target_malloc = FALSE;
	file = arg[1];
	if (!file || !ft_strcmp(file, "~"))
	{
		target = env_find_value("HOME", env);
		if (target == NULL)
			error_cd_home("HOME");
	}
	else if (!ft_strcmp(file, "-"))
	{
		target = env_find_value("OLDPWD", env);
		if (target == NULL)
			error_cd_home("OLDPWD");
	}
	else if (*file != '.' && *file != '/')
		target = get_absolute_path(file, target_malloc);
	else
		target = file;
	return (target);
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

static int	check_valid_path(t_env *env)
{
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putendl_fd("cd: error retrieving current directory", STDERR_FILENO);
		home = env_find_value("HOME", env);
		if (home == NULL || chdir(home) == -1)
		{
			chdir("/");
			return (error_cd_home("HOME"));
		}
	}
	else
		free(pwd);
	return (0);
}
