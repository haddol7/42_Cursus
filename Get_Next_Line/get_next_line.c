/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:43:10 by daeha             #+#    #+#             */
/*   Updated: 2024/01/13 11:00:23 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

//TODO 예외처리 컨셉
// 1. read() 실패 -> 해당 노드만 free
// 2. malloc() 실패 -> fd_list에 해당하는 모든 버퍼를 free

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list;
	char				*result;
	char				buf[BUFFER_SIZE + 1];
	size_t				buf_offset;
	ssize_t				read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || !find_fd(fd, &fd_list))
		return (NULL);

	while (1)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);

		if (read_bytes < 0)
			return (free_node(fd_list));

		if (is_in_newline_or_eof(buf, read_bytes, &buf_offset));
		{
			printf("fd->buffer\n%s\n", fd_list->buffer);
			printf("read_bytes\n%lu\n", read_bytes);
			printf("buf_offset\n%lu\n", buf_offset);
			
			if (!put_result(fd_list, &result, buf, buf_offset) || \
				!put_buf(fd_list, buf, read_bytes, buf_offset))
				return (free_node(fd_list));
			break ;
		}
		if (!put_buf(fd_list, buf, read_bytes, buf_offset))
			return (free_node(fd_list));
	}
	return (result);
}

//result의 경우에도 free 해야하는 경우가 있으므로 주의!
char	*free_node(t_fd_list *fd_list)
{
	return (NULL);
}

//링크드 리스트로 구성된 fd에 따른 저장된 buffer를 찾아주는 함수
//file.buffer는 무조건 malloc
int	find_fd(int fd, t_fd_list **file)
{
	while (*file != NULL && (*file)->fd != fd)
		*file = (*file)->next;
	if  (*file == NULL)
	{
		*file = (t_fd_list *)malloc(sizeof(t_fd_list));
		if (*file == NULL)
			return (0);
		(*file)->fd = fd;
		(*file)->len = 0;
		(*file)->buffer = NULL;
		(*file)->next = NULL;
	}
	return (1);
}

//버퍼에 저장된 문자열에서 \n 혹은 EOF까지의 문자열 + 기존 file에 있던 문자열을 result에 더해서 반환
//EOF 일 때 -> \0
//\n 일 때 -> 포함해서 저장
int	put_result(t_fd_list *file, char **res, char *buf, size_t offset)
{
	*res = (char *)malloc(sizeof(char) * (file->len + offset));
	if (*res == NULL)
		return (0);
	gnl_memmove(*res, file->buffer, file->len);
	gnl_memmove(*(res + file->len), buf, offset);
	file->len = 0;
	return (1);
}

//buffer에 남아있는 문자열을 fd 버퍼에 옮기는 함수
int	put_buf(t_fd_list *file, char *buf, ssize_t read_bytes, size_t offset)
{
	char	*new_file;
	size_t	len_left_buf;

	len_left_buf = read_bytes - offset;
	new_file = (char *)malloc(sizeof(char) * (file->len + len_left_buf));
	if (new_file == NULL)
		return (0);
	gnl_memmove(new_file, file->buffer, file->len);
	gnl_memmove(new_file + file->len, buf + offset, len_left_buf);
	if (file->buffer != NULL)
		free(file->buffer);
	file->buffer = new_file;
	file->len = file->len + len_left_buf;
	return (1);
}