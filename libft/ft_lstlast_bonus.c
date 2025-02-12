/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:07:36 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/19 16:16:59 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp_ptr;

	if (!(lst))
		return (NULL);
	tmp_ptr = lst;
	while (tmp_ptr->next)
		tmp_ptr = tmp_ptr->next;
	return (tmp_ptr);
}
