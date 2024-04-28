/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:04:36 by daeha             #+#    #+#             */
/*   Updated: 2024/04/28 15:21:53 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "libft.h"
#include "ft_printf.h"

typedef struct s_pipe
{
	int		a[2];
	int		b[2];
} t_pipe;

typedef struct s_param
{
	const int	argc;
	const char	**argv;
	const char	**envp;
} t_param;
