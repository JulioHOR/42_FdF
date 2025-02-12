/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:08:08 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	to_string_pointer(t_fmt_spec *tfmt_spec, void *ptr, int hex_or_ptr)
{
	char	*result;

	if (!(ptr))
	{
		tfmt_spec->out_cont = ft_strdup("(nil)");
		return ;
	}
	to_string_hex(tfmt_spec, (uint64_t) ptr, 0, hex_or_ptr);
	result = tfmt_spec->out_cont;
	tfmt_spec->out_cont = ft_strjoin("0x", tfmt_spec->out_cont);
	free(result);
}
