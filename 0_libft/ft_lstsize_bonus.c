/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:24:42 by daeha             #+#    #+#             */
/*   Updated: 2023/11/19 18:41:39 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	**lst;
// 	t_list	*lst1;
// 	t_list	*lst2;
// 	t_list	*lst3;

// 	lst = &lst3;
// 	lst1 = ft_lstnew(ft_strdup("first"));
// 	lst2 = ft_lstnew(ft_strdup("second"));
// 	lst3 = ft_lstnew(ft_strdup("third"));

// 	ft_lstadd_front(lst, lst2);
// 	ft_lstadd_front(lst, lst1);

// 	printf("%d", ft_lstsize(lst1));
// 	printf("\n%d", ft_lstsize(lst2));
// 	printf("\n%d", ft_lstsize(lst3));

// 	return (0);
// }
