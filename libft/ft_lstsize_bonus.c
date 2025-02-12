/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:27:55 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/19 16:06:24 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		counter;
	t_list	*tmp_ptr;

	if (!(lst))
		return (0);
	counter = 1;
	tmp_ptr = lst;
	while (tmp_ptr->next)
	{
		tmp_ptr = tmp_ptr->next;
		counter++;
	}
	return (counter);
}
