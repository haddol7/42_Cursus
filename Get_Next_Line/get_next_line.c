/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:43:10 by daeha             #+#    #+#             */
/*   Updated: 2024/01/12 17:20:31 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//TODO 예외처리 컨셉
// 1. read() 실패 -> 어떻게 해줘야할까?
// 2. malloc() 실패 -> fd_list에 해당하는 모든 버퍼를 free

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list;
	char				*result;
	char				buf[BUFFER_SIZE + 1];
	size_t				buf_offset;
	ssize_t				read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fd_list = find_fd(fd, fd_list);
	while (1)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free_list(fd_list));
		if (is_in_newline_or_eof(buf, read_bytes, &buf_offset))
		{
			if (!put_result(&result, buf, fd_list->buffer, buf_offset) && \
				!put_left_buf(buf, &fd_list->buffer, read_bytes, buf_offset))
				return (free_list(fd_list));
			break ;
		}
		if (!put_left_buffer(buf, &fd_list->buffer, read_bytes, buf_offset))
			return (free_list(fd_list));
	}
	return (result);
}

//result
char	*free_list(t_fd_list *fd_list)
{
	return (NULL);
}

//링크드 리스트로 구성된 fd에 따른 저장된 buffer를 찾아주는 함수
//file.buffer는 무조건 malloc
t_fd_list	*find_fd(int fd, t_fd_list *file)
{
}

//버퍼에 저장된 문자열에서 \n 혹은 EOF까지의 문자열 + 기존 file에 있던 문자열을 result에 더해서 반환
//EOF 일 때 -> \0
//\n 일 때 -> 포함해서 저장
/*
int	put_result(char **res, char *buf, char *file, size_t offset)
{
	size_t	len_file;

	len_file = gnl_strlen(file);
	*res = (char *)malloc(sizeof(char) * (len_file + offset));
	if (*res = NULL)
		return (0);
	(*res)[0] = '\0';
	gnl_memmove(*res, file, len_file);
	gnl_memmove(*(res + len_file), buf, offset);
	file[0] = '\0';
	return (1);
}
*/

int	put_result(t_fd_list *file, char **res, char *buf, size_t offset)
{
	*res = (char *)malloc(sizeof(char) * (file->len + offset));
	if (*res = NULL)
		return (0);
	gnl_memmove(*res, file, file->len);
	gnl_memmove(*(res + file->len), buf, offset);
	file->buffer[0] = '\0';
	return (1);
}

//buffer에 남아있는 문자열을 fd 버퍼에 옮기는 함수

/*
int	put_left_buf(char *buf, char **file, ssize_t read_bytes, size_t offset)
{
	char	*new_file;
	size_t	len_file;
	size_t	len_left_buf;

	len_file = gnl_strlen(*file);
	len_left_buf = read_bytes - offset;
	new_file = (char *)malloc(sizeof(char) * (len_file + len_left_buf));
	if (new_file == NULL)
		return (0);
	new_file[0] = '\0';
	gnl_memmove(new_file, *file, len_file);
	gnl_memmove(new_file + len_file, buf + offset, len_left_buf);
	if (*file != NULL)
		free(*file);
	*file = new_file;
	return (1);
}
*/

int	put_left_buf(t_fd_list *file, char *buf, ssize_t read_bytes, size_t offset)
{
	char	*new_file;
	size_t	len_left_buf;

	len_left_buf = read_bytes - offset;
	new_file = (char *)malloc(sizeof(char) * (file->len + len_left_buf));
	if (new_file == NULL)
		return (0);
	gnl_memmove(new_file, *file, file->len);
	gnl_memmove(new_file + file->len, buf + offset, len_left_buf);
	if (file->buffer != NULL)
		free(file->buffer);
	file->buffer = new_file;
	file->len = file->len + len_left_buf;
	return (1);
}
