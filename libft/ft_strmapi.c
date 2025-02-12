/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:30:40 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/12 15:55:01 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*array;
	int		array_len;
	int		i;

	array_len = ft_strlen(s);
	if (!s || !f)
		return ((void *) 0);
	array = (char *) malloc ((array_len + 1) * sizeof(char));
	if (!(array))
		return ((void *) 0);
	array[array_len] = '\0';
	i = -1;
	while (++i < array_len)
		array[i] = f(i, s[i]);
	return (array);
}
