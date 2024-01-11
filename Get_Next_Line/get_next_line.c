/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:43:10 by daeha             #+#    #+#             */
/*   Updated: 2024/01/11 18:40:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_fd_list	*file;
	char				buffer[BUFFER_SIZE + 1];
	size_t				buffer_offset;
	ssize_t				read_bytes;
	char				*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	file = find_fd(fd, file);
	result = NULL;
	while (read_bytes = read(fd, buffer, BUFFER_SIZE))
	{
		if(buffer_offset = is_in_newline_or_eof(buffer, read_bytes))
		{
			result = put_result(result, buffer, file->buffer, buffer_offset);
			put_left_buffer(buffer, file->buffer, buffer_offset);
			break;
		}
		put_left_buffer(buffer, file->buffer, buffer_offset);
	}
	return (result);
}

t_fd_list	*find_fd(int fd, t_fd_list *file)
{
	
}

size_t	is_in_newline_or_eof(char *buffer, ssize_t read_bytes)
{
	size_t	buffer_offset;
	
	buffer_offset = 0;
	if (read_bytes < BUFFER_SIZE)
		return (1);
	while (buffer_offset < BUFFER_SIZE)
	{
		if (buffer[buffer_offset] == '\n')
			return (buffer_offset);
		buffer_offset++;
	}
	return (0);
}

char	*put_result(char *result, char *buffer, char *file_buffer, size_t buffer_offset)
{
	char	*new_result;
	size_t	len_result;
	size_t	len_buffer;

	len_result = gnl_strlen(result);
	len_buffer = buffer_offset;
	new_result = (char *)malloc(sizeof(char) * (len_result + len_buffer + 1));
	if (new_result = NULL)
	//TODO 모든 malloc free
	{

	}
	new_result = '\0';
	gnl_strlcat(new_result, buffer, len_result + len_buffer + 1);
	gnl_strlcat(new_result, file_buffer, len_result + len_buffer + 1);
	free(result);
	return (new_result);
}

void	put_left_buffer(char *buffer, char *file_buffer, size_t buffer_offset)
{
	char	*new_file_buffer;

	 
}
