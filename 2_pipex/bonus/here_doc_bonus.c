/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:00:50 by daeha             #+#    #+#             */
/*   Updated: 2024/05/07 21:14:20 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*name_here_doc(void);
static int	px_strcmp(char *str1, char *str2);

char	*here_doc(char *limiter)
{
	int		fd;
	char	*doc_name;
	char	*str;

	doc_name = name_here_doc();
	fd = open(doc_name, O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
		terminate("pipex : open");
	write(STDOUT_FILENO, "heredoc> ", 9);
	while (1)
	{
		str = get_next_line(STDIN_FILENO);
		if (str != NULL)
		{
			if (px_strcmp(limiter, str))
				break ;
			if (str[ft_strlen(str) - 1] == '\n')
				write(STDOUT_FILENO, "heredoc> ", 9);
			write(fd, str, ft_strlen(str));
			free(str);
		}
	}
	free(str);
	close(fd);
	return (doc_name);
}

static char	*name_here_doc(void)
{
	char	*doc_name;
	char	*tmp;

	doc_name = ft_strdup("here_doc.tmp");
	while (!access(doc_name, F_OK))
	{
		tmp = ft_strjoin(doc_name, ".tmp");
		free(doc_name);
		doc_name = tmp;
	}
	return (doc_name);
}

static int	px_strcmp(char *str1, char *str2)
{
	size_t	len_str1;
	size_t	len_str2;

	len_str1 = ft_strlen(str1);
	len_str2 = ft_strlen(str2);
	if (len_str1 + 1 != len_str2)
		return (0);
	if (ft_strncmp(str1, str2, len_str1))
		return (0);
	return (1);
}
