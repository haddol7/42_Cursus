/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:00:50 by daeha             #+#    #+#             */
/*   Updated: 2024/04/30 22:34:27 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*here_doc(char *limiter)
{
	int		fd;
	char	*doc_name;
	char	*tmp;
	char	*str;

	doc_name = ft_strdup("here_doc.tmp");
	while (!access(doc_name, F_OK))
	{
		tmp = ft_strjoin(doc_name, ".tmp");
		free(doc_name);
		doc_name = tmp;
	}
	fd = open(doc_name, O_WRONLY | O_CREAT, 0666);
	while (1)
	{
		str = get_next_line(STDIN_FILENO);
		if (str != NULL && !ft_strncmp(limiter, str, (int)ft_strlen(str) - 1))
		{
			if (ft_strncmp(limiter, str, (int)ft_strlen(str) - 1))
			{
				free(str);
				break;
			}
			ft_putstr_fd(str, fd);
			free(str);
		}
	}
	close(fd);
	return (doc_name);
}
