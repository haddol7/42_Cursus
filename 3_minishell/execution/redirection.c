/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:21:20 by daeha             #+#    #+#             */
/*   Updated: 2024/06/04 22:41:41 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int g_status;

int	input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		perror(filename);
		g_status = 1;
	}
	return (fd);
}

int	here_doc(char *delim)
{
	int		fd;
	char	*str;

	fd = open("/tmp/here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		perror("here_doc");
		g_status = 1;
	}
	while (1)
	{
		str = get_next_line(STDIN_FILENO);
		if (ft_strlen(str) - 1 == ft_strlen(delim) && !ft_strncmp(str, delim, ft_strlen(delim) - 1))
		{
			free(str);
			break;
		}
		write(fd, str, ft_strlen(str));
		free(str);
	}
	return (fd);
}

int	output(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		perror(filename);
		g_status = 1;
	}
	return (fd);
}

int	append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		perror(filename);
		g_status = 1;
	}
	return (fd);
}
