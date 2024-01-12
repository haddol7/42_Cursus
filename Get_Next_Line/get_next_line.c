/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:43:10 by daeha             #+#    #+#             */
/*   Updated: 2024/01/12 14:51:07 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//TODO 예외처리 컨셉
// 1. read() 실패 -> 어떻게 해줘야할까?
// 2. malloc() 실패 -> fd_list에 해당하는 모든 버퍼를 free

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list;
	char				buffer[BUFFER_SIZE + 1];
	size_t				buffer_offset;
	ssize_t				read_bytes;
	char				*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fd_list = find_fd(fd, fd_list);
	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free_list(fd_list));
		if (is_in_newline_or_eof(buffer, read_bytes, &buffer_offset))
		{
			if (!put_result(&result, buffer, fd_list->buffer, buffer_offset) && \
				!put_left_buffer(buffer, fd_list->buffer, buffer_offset))
				return (free_list(fd_list));
			break ;
		}
		if (!put_left_buffer(buffer, fd_list->buffer, buffer_offset))
			return (free_list(fd_list));
	}
	return (result);
}

char	*free_list(t_fd_list *fd_list)
{
	return (NULL);
}

//링크드 리스트로 구성된 fd에 따른 저장된 buffer를 찾아주는 함수
t_fd_list	*find_fd(int fd, t_fd_list *file)
{
}

//read 함수 호출 이후 저장된 버퍼 안에 \n이 있는지, EOF에 도달했는지 확인하는 함수
size_t	is_in_newline_or_eof(char *buffer, ssize_t read_bytes, size_t *offset)
{
	*offset = 0;
	if (read_bytes < BUFFER_SIZE)
		return (1);
	while (*offset < BUFFER_SIZE)
	{
		if (buffer[*offset] == '\n')
			return (1);
		offset++;
	}
	return (0);
}

//버퍼에 저장된 문자열을 \n을 포함해서 기존의 result에 복사하는 함수
char	*put_result(char *result, char *buffer, char *file, size_t offset)
{
	char	*new_result;
	size_t	len_result;
	size_t	len_buffer;

	len_result = gnl_strlen(result);
	len_buffer = offset;
	new_result = (char *)malloc(sizeof(char) * (len_result + len_buffer + 1));
	if (new_result = NULL)
		return (NULL);
	new_result = '\0';
	gnl_strlcat(new_result, buffer, len_result + len_buffer + 1);
	gnl_strlcat(new_result, file, len_result + len_buffer + 1);
	free(result);
	return (new_result);
}

//buffer에 남아있는 문자열을 fd 버퍼에 옮기는 함수
void	put_left_buf(char *buf, char *file, ssize_t read_bytes, size_t offset)
{

}
