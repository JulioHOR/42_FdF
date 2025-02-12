/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:10:14 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/07 21:05:37 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_substring;
	size_t	s_len;
	size_t	real_substring_len;
	size_t	i;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	real_substring_len = len;
	if (len > (s_len - start))
		real_substring_len = s_len - start;
	new_substring = (char *) malloc((real_substring_len + 1));
	if (!new_substring)
		return (((void *) 0));
	i = 0;
	while ((i < real_substring_len) && (s[start] != '\0'))
		new_substring[i++] = s[start++];
	new_substring[i] = '\0';
	return (new_substring);
}
