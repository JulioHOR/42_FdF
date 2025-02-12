/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:30:40 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/12 16:13:11 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		array_len;
	int		i;

	array_len = ft_strlen(s);
	if (!s || !f)
		return ;
	i = -1;
	while (++i < array_len)
		f(i, &(s[i]));
}
