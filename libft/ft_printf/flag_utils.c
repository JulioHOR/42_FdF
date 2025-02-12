/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:49:13 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	contains_nil(char *str)
{
	size_t	str_len;
	size_t	i;
	size_t	j;
	char	*nil_str;

	nil_str = "(nil)";
	str_len = ft_strlen(str);
	if (ft_strlen(str) < 5)
		return (0);
	i = 0;
	j = 0;
	while (i < str_len && j < 5)
	{
		if (str[i] == nil_str[j] && j + 1 <= 5)
			j++;
		if (j == 5)
			return (1);
		i++;
	}
	return (0);
}
