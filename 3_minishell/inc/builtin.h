/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:42:49 by daeha             #+#    #+#             */
/*   Updated: 2024/06/12 20:49:26 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "expansion.h"

void	ms_cd(char **arg, t_env *stat);
void	ms_env(char **arg, t_env *stat);
void	ms_pwd(char **arg, t_env *stat);
void	ms_echo(char **arg, t_env *stat);
void	ms_exit(char **arg, t_env *stat);
void	ms_unset(char **arg, t_env *stat);
void	ms_export(char **arg, t_env *stat);

#endif
