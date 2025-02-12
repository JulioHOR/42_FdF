/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:22:41 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/13 19:07:40 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_size;
	size_t	dst_size;
	size_t	actual_amount_of_bytes_to_cpy;

	src_size = ft_strlen(src);
	dst_size = ft_strlen(dst);
	if (size <= dst_size)
		return (src_size + size);
	actual_amount_of_bytes_to_cpy = (size - dst_size - 1);
	i = dst_size;
	j = 0;
	while ((j < actual_amount_of_bytes_to_cpy) && (src[j] != '\0'))
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (src_size + dst_size);
}
