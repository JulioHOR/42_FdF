/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string_unsigned_int.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:44:06 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_arr(char *array, int array_pos, unsigned int n)
{
	while (array_pos >= 0)
	{
		array[array_pos--] = ((n % 10) + '0');
		n = (n / 10);
	}
}

static char	*ft_unsigned_itoa(unsigned int n)
{
	char				*array;
	int					n_len;
	unsigned int		n_cpy;
	int					i;

	n_cpy = n;
	if (n_cpy == 0)
		n_len = 1;
	else
	{
		i = 0;
		while (n_cpy != 0)
		{
			n_cpy = (n_cpy / 10);
			i++;
		}
		n_len = i;
	}
	array = (char *) malloc(n_len + 1);
	if (!(array))
		return (NULL);
	array[n_len] = '\0';
	fill_arr(array, (n_len - 1), n);
	return (array);
}

void	to_string_unsigned_int(t_fmt_spec *tfmt_spec, unsigned int n)
{
	tfmt_spec->out_cont = ft_unsigned_itoa(n);
}
