/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:42:49 by daeha             #+#    #+#             */
/*   Updated: 2024/06/26 14:56:31 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "signals.h"
# include "expansion.h"

# define KEY '='
# define VALUE '\0'

int		ms_cd(char **arg, t_env *env);
void	ms_env(char **arg, t_env *env);
void	ms_pwd(void);
void	ms_echo(char **arg);
void	ms_exit(char **arg);
void	ms_unset(char **arg, t_env *env);
void	ms_export(char **arg, t_env *env);

//cd_utils.c
int		error_cd_home(char *keyword);
int		error_cd_enoent(char *file, char *target, t_bool target_malloc);

//export_utils.c
void	display_declare_list(t_env *env);

#endif
