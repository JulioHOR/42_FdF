/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:35:55 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/20 21:11:18 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	chk_malloc(t_list *ptr_iters_copied_list, t_list *head, \
	void (*del)(void *), void *n_content)
{
	if (!ptr_iters_copied_list)
	{
		if (del)
			del(n_content);
		ft_lstclear(&head, del);
		return (1);
	}
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head_copied_lst;
	t_list	*ptr_iters_copied_list;
	t_list	*ptr_that_iters_list;
	t_list	*temp_ptr;
	void	*n_content;

	if (!lst)
		return (NULL);
	temp_ptr = NULL;
	head_copied_lst = NULL;
	ptr_that_iters_list = lst;
	while (ptr_that_iters_list)
	{
		n_content = f(ptr_that_iters_list->content);
		ptr_iters_copied_list = ft_lstnew(n_content);
		if (chk_malloc(ptr_iters_copied_list, head_copied_lst, del, n_content))
			return (NULL);
		if (!head_copied_lst)
			head_copied_lst = ptr_iters_copied_list;
		if (temp_ptr)
			temp_ptr->next = ptr_iters_copied_list;
		temp_ptr = ptr_iters_copied_list;
		ptr_that_iters_list = ptr_that_iters_list->next;
	}
	return (head_copied_lst);
}
