/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_force_plus_sign.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 20:52:26 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	force_plus_sign_flag_applier(t_fmt_spec *tfmt_spec)
{
	char	*temp_ptr;

	if (!(ft_strcmp_homemade("(nil)", tfmt_spec->out_cont)))
		return ;
	if (find_char(tfmt_spec->out_cont, '-', 0) != -1)
		return ;
	temp_ptr = tfmt_spec->out_cont;
	tfmt_spec->out_cont = ft_strjoin("+", tfmt_spec->out_cont);
	tfmt_spec->out_cont_len = ft_strlen(tfmt_spec->out_cont);
	free(temp_ptr);
}
