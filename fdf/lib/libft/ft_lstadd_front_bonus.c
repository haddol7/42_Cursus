/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:36:02 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 17:12:07 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*lst;
// 	t_list	*new;

// 	lst = ft_lstnew("original");
// 	new = ft_lstnew("front");
// 	ft_lstadd_front(&lst, new);

// 	while (lst != NULL)
// 	{
// 		printf("%s\n", lst->content);
// 		lst = lst->next;
// 	}
// 	return (0);
// }
