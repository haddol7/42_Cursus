/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:58:40 by daeha             #+#    #+#             */
/*   Updated: 2023/11/20 16:06:54 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*temp;
	void	*temp_content;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	lst_new = NULL;
	while (lst != NULL)
	{
		temp_content = f(lst->content);
		temp = ft_lstnew(temp_content);
		if (temp == NULL || temp_content == NULL)
		{
			if (temp == NULL)
				del(temp_content);
			else if (temp_content == NULL)
				free(temp);
			ft_lstclear(&lst_new, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_new, temp);
		lst = lst->next;
	}
	return (lst_new);
}

// static	void	*f(void	*content)
// {
// 	return ("!");
// }

// static void	del(void	*content)
// {
// 	content = NULL;
// }

// #include <stdio.h>

// int	main(void)
// {
// 	t_list	*lst1;
// 	t_list	*lst2;
// 	t_list	*lst3;
// 	t_list	*lst_new;

// 	lst1 = ft_lstnew("lst1");
// 	lst2 = ft_lstnew("lst2");
// 	lst3 = ft_lstnew("lst3");
// 	ft_lstadd_back(&lst1, lst2);
// 	ft_lstadd_back(&lst2, lst3);
// 	lst_new = ft_lstmap(lst1, f, del);
// 	while (lst_new != NULL)
// 	{
// 		printf("%s", lst_new->content);
// 		lst_new = lst_new->next;
// 	}
// 	ft_lstclear(&lst1, del);
// 	ft_lstclear(&lst_new, del);
// 	return (0);
// }
