/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:47:16 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/28 01:55:03 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_hex(char *str, int str_len, const char *hex_characters)
{
	int	i;
	int	j;
	int	matches_hex_char;

	matches_hex_char = 0;
	i = -1;
	j = -1;
	while (++i < str_len)
	{
		matches_hex_char = 0;
		while (++j < 16)
		{
			// OI OI REMOVA-ME
			ft_printf("j é: %d\n", j);
			if (str[i] == hex_characters[j]
				|| str[i] == (hex_characters[j] - 32))
			{
				matches_hex_char = 1;
				break ;
			}
		}
		if (!(matches_hex_char))
			return (0);
	}
	return (1);
}

int	is_hex(char *str)
{
	size_t		str_len;
	const char	*hex_characters;

	if (!(str))
		return (0);
	hex_characters = "0123456789abcdef";
	str_len = ft_strlen(str);
	return (check_hex(str, str_len, hex_characters));
}
