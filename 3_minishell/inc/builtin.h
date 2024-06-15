/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:42:49 by daeha             #+#    #+#             */
/*   Updated: 2024/06/15 20:33:32 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "expansion.h"

# define KEY '='
# define VALUE '\0'

void	ms_cd(char **arg, t_env *env);
void	ms_env(char **arg, t_env *env);
void	ms_pwd(void);
void	ms_echo(char **arg);
void	ms_exit(char **arg, t_env *env);
void	ms_unset(char **arg, t_env *env);
void	ms_export(char **arg, t_env *env);
t_bool	is_env_key_valid(char *str);

#endif
