/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:52:43 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 17:12:27 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*lst1;
// 	t_list	lst2;

// 	lst1 = ft_lstnew("lst1");
// 	lst2.content = "lst2";
// 	ft_lstadd_back(&lst1, &lst2);
// 	printf("%s", lst1->next->content);
// 	return (0);
// }
