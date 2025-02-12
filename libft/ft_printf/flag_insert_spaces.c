/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_insert_spaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:28:28 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	work_on_output_str(t_fmt_spec *tfmt_spec)
{
	char	*new_str;

	new_str = ft_strjoin(" ", tfmt_spec->out_cont);
	if (!(new_str))
	{
		free(tfmt_spec->out_cont);
		tfmt_spec->out_cont = NULL;
		return ;
	}
	free(tfmt_spec->out_cont);
	tfmt_spec->out_cont = new_str;
	tfmt_spec->out_cont_len = ft_strlen(tfmt_spec->out_cont);
}

void	insert_spaces_flag_applier(t_fmt_spec *tfmt_spec)
{
	if (contains_nil(tfmt_spec->out_cont)
		|| (tfmt_spec->flags.precision == 1
			&& tfmt_spec->data_type != TYPE_INT
			&& tfmt_spec->data_type != TYPE_EXPANDED_BASE_INT
			&& tfmt_spec->data_type != TYPE_POINTER))
	{
		tfmt_spec->flags.insert_space = -1;
		return ;
	}
	if (find_char(tfmt_spec->out_cont, '-', 0) != -1
		&& tfmt_spec->data_type != TYPE_STRING)
		return ;
	tfmt_spec->flags.field_width = 1;
	work_on_output_str(tfmt_spec);
}
