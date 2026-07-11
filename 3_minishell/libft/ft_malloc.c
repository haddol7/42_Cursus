/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:33:44 by daeha             #+#    #+#             */
/*   Updated: 2024/06/19 22:49:11 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (mem == NULL)
	{
		perror("minishell: malloc:");
		exit(12);
	}
	return (mem);
}
