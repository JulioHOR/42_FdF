/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_especifier_content.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:48:33 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	raw_content_part(t_fmt_spec *tfmt_spec, va_list var_args)
{
	if (tfmt_spec->data_type == TYPE_CHAR)
		to_string_char(tfmt_spec, va_arg(var_args, unsigned int));
	if (tfmt_spec->data_type == TYPE_STRING)
		to_string_string(tfmt_spec, va_arg(var_args, char *));
	if (tfmt_spec->data_type == TYPE_POINTER)
		to_string_pointer(tfmt_spec, va_arg(var_args, void *), 1);
	if (tfmt_spec->data_type == TYPE_INT)
		to_string_int(tfmt_spec, va_arg(var_args, int));
	if (tfmt_spec->data_type == TYPE_EXPANDED_BASE_INT)
		to_string_int(tfmt_spec, va_arg(var_args, int));
	if (tfmt_spec->data_type == TYPE_UNSIGNED_INT)
		to_string_unsigned_int(tfmt_spec, va_arg(var_args, unsigned int));
	if (tfmt_spec->data_type == TYPE_LOWER_HEX)
		to_string_hex(tfmt_spec, va_arg(var_args, uintptr_t), 0, 0);
	if (tfmt_spec->data_type == TYPE_UPPER_HEX)
		to_string_hex(tfmt_spec, va_arg(var_args, uintptr_t), 1, 0);
	if (tfmt_spec->data_type == TYPE_PERCENT_SIGN)
		to_string_percent(tfmt_spec);
	if ((tfmt_spec->out_cont) && tfmt_spec->data_type == TYPE_CHAR
		&& tfmt_spec->out_cont[0] == 0)
		tfmt_spec->out_cont_len = 1;
	else
		if (tfmt_spec->out_cont)
			tfmt_spec->out_cont_len = ft_strlen(tfmt_spec->out_cont);
}

void	flags_part(t_fmt_spec *tfmt_spec)
{
	t_flags	*flag_option;

	flag_option = &(tfmt_spec->flags);
	if (flag_option->precision == 1)
		precision_flag_applier(tfmt_spec);
	if (flag_option->fill_zero == 1)
		fill_zero_flag_applier(tfmt_spec);
	if (flag_option->force_plus_sign == 1)
		force_plus_sign_flag_applier(tfmt_spec);
	if (flag_option->prefixe == 1)
		prefixe_flag_applier(tfmt_spec);
	if (flag_option->alignment == 1)
		alignment_flag_applier(tfmt_spec);
	if (flag_option->insert_space == 1)
		insert_spaces_flag_applier(tfmt_spec);
	if (flag_option->field_width == 1)
		width_flag_applier(tfmt_spec);
}
