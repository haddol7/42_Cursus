/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:42:49 by daeha             #+#    #+#             */
/*   Updated: 2024/07/02 17:44:05 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_BONUS_H
# define BUILTIN_BONUS_H

# include "signals_bonus.h"
# include "expansion_bonus.h"

# define KEY '='
# define VALUE '\0'

int		ms_cd(char **arg, t_env *env);
void	ms_env(char **arg, t_env *env);
void	ms_pwd(void);
void	ms_echo(char **arg);
void	ms_exit(char **arg, t_bool is_forked);
void	ms_unset(char **arg, t_env *env);
void	ms_export(char **arg, t_env *env);

//cd_utils.c
int		error_cd_home(char *keyword);
int		error_cd_enoent(char *file, char *target, t_bool target_malloc);

//export_utils.c
void	display_declare_list(t_env *env);

#endif
