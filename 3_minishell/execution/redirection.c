/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:21:20 by daeha             #+#    #+#             */
/*   Updated: 2024/06/05 14:11:40 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int	g_status;

static void	redir_error(char *name);

int	input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		redir_error(filename);
	return (fd);
}

int	here_doc(char *delim)
{
	char	*str;
	int		len_d;
	int		len_s;
	int		fd;

	fd = open("/tmp/here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		redir_error(delim);
	len_d = ft_strlen(delim);
	while (TRUE)
	{	
		ft_putstr_fd("> ", STDOUT_FILENO);
		str = get_next_line(STDIN_FILENO);
		if (str)
			len_s = ft_strlen(str);
		if (!str || (len_s == len_d + 1 && !ft_strncmp(str, delim, len_d)))
			break ;
		write(fd, str, len_s);
		free(str);
	}
	if (str != NULL)
		free(str);
	close(fd);
	return (input("/tmp/here_doc.tmp"));
}

int	output(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		redir_error(filename);
	return (fd);
}

int	append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		redir_error(filename);
	return (fd);
}

static void	redir_error(char *name)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	perror(name);
	g_status = 1;
}
