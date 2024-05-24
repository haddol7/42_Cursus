/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:58:57 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 17:12:57 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}

// static void	del(void	*content)
// {
// 	free(content);
// }

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*lst1;

// 	lst = ft_lstnew(ft_strdup("lst"));
// 	lst1 = ft_lstnew(ft_strdup("lst1"));
// 	lst->next = lst1;
// 	ft_lstdelone(lst1, 0);
// 	ft_lstdelone(lst, 0);
// 	return (0);
// }
