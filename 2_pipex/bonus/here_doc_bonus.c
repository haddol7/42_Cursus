/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:00:50 by daeha             #+#    #+#             */
/*   Updated: 2024/04/30 23:13:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*name_here_doc(void);

char	*here_doc(char *limiter)
{
	int		fd;
	char	*doc_name;
	char	*str;

	doc_name = name_here_doc();
	fd = open(doc_name, O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
		terminate("pipex : open");
	while (1)
	{
		str = get_next_line(STDIN_FILENO);
		if (str != NULL && !ft_strncmp(limiter, str, (int)ft_strlen(str) - 1))
		{
			if (ft_strncmp(limiter, str, (int)ft_strlen(str) - 1))
			{
				free(str);
				break ;
			}
			ft_putstr_fd(str, fd);
			free(str);
		}
	}
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
