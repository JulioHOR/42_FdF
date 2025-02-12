/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:36:31 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/19 19:59:51 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!(*lst) || !(del))
		return ;
	ft_lstclear(&((*lst)->next), del);
	if ((*lst)->content)
		del((*lst)->content);
	free(*lst);
	*lst = NULL;
}
