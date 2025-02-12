/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_prefixe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:48:30 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_all_zero(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] != '0')
			return (0);
	return (1);
}

void	prefixe_flag_applier(t_fmt_spec *tfmt_spec)
{
	char	*temp_ptr;

	if (tfmt_spec->data_type != TYPE_LOWER_HEX
		&& tfmt_spec->data_type != TYPE_UPPER_HEX)
		return ;
	temp_ptr = tfmt_spec->out_cont;
	if (tfmt_spec->out_cont_len == 0 || is_all_zero(tfmt_spec->out_cont)
		|| contains_nil(tfmt_spec->out_cont))
		return ;
	if (tfmt_spec->data_type == TYPE_LOWER_HEX)
		tfmt_spec->out_cont = ft_strjoin("0x", tfmt_spec->out_cont);
	else
		tfmt_spec->out_cont = ft_strjoin("0X", tfmt_spec->out_cont);
	tfmt_spec->out_cont_len = ft_strlen(tfmt_spec->out_cont);
	free(temp_ptr);
}
