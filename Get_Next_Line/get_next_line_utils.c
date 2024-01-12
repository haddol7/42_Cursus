/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:15:37 by daeha             #+#    #+#             */
/*   Updated: 2024/01/12 17:06:37 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//read 함수 호출 이후 저장된 버퍼 안에 \n이 있는지, EOF에 도달했는지 확인하는 함수
//offset은 \n 뒤에 있는 index를 가르킨다
//EOF에 도달했을 때, buffer에 '\0'을 넣는다.
size_t	is_in_newline_or_eof(char *buffer, ssize_t read_bytes, size_t *offset)
{
	*offset = 0;
	if (read_bytes < BUFFER_SIZE)
	{
		*offset = read_bytes;
		buffer[*offset++] = '\0';
		return (1);
	}
	while (*offset < BUFFER_SIZE)
	{
		if (buffer[*offset++] == '\n')
			return (1);
		offset++;
	}
	buffer[*offset] = '\0';
	return (0);
}

size_t	gnl_strlen(char *buffer)
{
	size_t	cnt;

	cnt = 0;
	if (buffer == NULL)
		return (0);
	while (buffer[cnt] != '\0')
		cnt++;
	return (cnt);
}
