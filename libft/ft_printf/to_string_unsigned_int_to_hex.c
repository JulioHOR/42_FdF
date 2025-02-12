/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string_unsigned_int_to_hex.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:55:03 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_get_hex_len(unsigned int number)
{
	int	length;

	length = 0;
	if (!(number))
		return (1);
	while (number)
	{
		number /= 16;
		length++;
	}
	return (length);
}

char	*unsigned_hex_int_to_hex(unsigned int number, int case_flag)
{
	int		length;
	char	*array;
	char	*hex_representation;

	if (case_flag)
		hex_representation = "0123456789ABCDEF";
	else
		hex_representation = "0123456789abcdef";
	length = hex_get_hex_len(number);
	array = (char *) malloc(length + 1);
	if (!(array))
		return (NULL);
	array[length] = '\0';
	length--;
	if (!(number))
		array[0] = '0';
	else
	{
		while (number)
		{
			array[length--] = hex_representation[number % 16];
			number /= 16;
		}
	}
	return (array);
}

static int	ptr_get_hex_len(uint64_t number)
{
	int	length;

	length = 0;
	if (!(number))
		return (1);
	while (number)
	{
		number /= 16;
		length++;
	}
	return (length);
}

char	*unsigned_ptr_int_to_hex(uint64_t number, int case_flag)
{
	int		length;
	char	*array;
	char	*hex_representation;

	if (case_flag)
		hex_representation = "0123456789ABCDEF";
	else
		hex_representation = "0123456789abcdef";
	length = ptr_get_hex_len(number);
	array = (char *) malloc(length + 1);
	if (!(array))
		return (NULL);
	array[length] = '\0';
	length--;
	if (!(number))
		array[0] = '0';
	else
	{
		while (number)
		{
			array[length--] = hex_representation[number % 16];
			number /= 16;
		}
	}
	return (array);
}
