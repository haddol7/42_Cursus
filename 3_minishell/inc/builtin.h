/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:42:49 by daeha             #+#    #+#             */
/*   Updated: 2024/06/15 17:26:35 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "expansion.h"

void	ms_cd(char **arg, t_env *stat);
void	ms_env(char **arg, t_env *stat);
void	ms_pwd(char **arg, t_env *stat);
void	ms_echo(char **arg);
void	ms_exit(char **arg, t_env *stat);
void	ms_unset(char **arg, t_env *stat);
void	ms_export(char **arg, t_env *stat);

#endif
