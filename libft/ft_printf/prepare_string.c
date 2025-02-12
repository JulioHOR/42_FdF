/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:29:58 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	resolve_flag_compatibility_with_data_type(t_fmt_spec *tfmt_spec)
{
	t_data_type	*data_type;

	data_type = &(tfmt_spec->data_type);
	if (tfmt_spec->flags.fill_zero && (*data_type == TYPE_STRING
			|| *data_type == TYPE_CHAR || *data_type == TYPE_PERCENT_SIGN
			|| *data_type == TYPE_POINTER))
	{
		tfmt_spec->flags.fill_zero = -1;
		width_flag_checker(tfmt_spec);
	}
	if (tfmt_spec->flags.precision && (*data_type == TYPE_CHAR
			|| *data_type == TYPE_PERCENT_SIGN))
		tfmt_spec->flags.precision = -1;
	if (tfmt_spec->flags.prefixe && (
			*data_type != TYPE_LOWER_HEX && *data_type != TYPE_UPPER_HEX))
		tfmt_spec->flags.prefixe = -1;
	if (tfmt_spec->flags.force_plus_sign && (*data_type != TYPE_INT
			&& *data_type != TYPE_EXPANDED_BASE_INT
			&& *data_type != TYPE_POINTER))
		tfmt_spec->flags.force_plus_sign = -1;
	if (tfmt_spec->flags.insert_space && (*data_type != TYPE_INT
			&& *data_type != TYPE_EXPANDED_BASE_INT
			&& *data_type != TYPE_POINTER))
		tfmt_spec->flags.insert_space = -1;
}

// This function will override some flags if other prevalent flags are present.
// It will also check if the active flags are compatible with the data type. If
// they aren't, the flags will be disabled.
static void	resolve_flag_conflicts(t_fmt_spec *tfmt_spec)
{
	t_flags		*flags;

	while (tfmt_spec)
	{
		flags = &(tfmt_spec->flags);
		if (flags->alignment && flags->fill_zero)
			flags->fill_zero = -1;
		if (flags->precision && flags->fill_zero)
		{
			flags->fill_zero = -1;
			flags->field_width = 1;
		}
		if (flags->force_plus_sign && flags->insert_space)
			flags->insert_space = -1;
		resolve_flag_compatibility_with_data_type(tfmt_spec);
		tfmt_spec = tfmt_spec->next_fmt_spec;
	}
}

static int	fill_char_array(t_input *tinput, size_t input_idx,
	int output_idx, char *output_str)
{
	t_fmt_spec	*curr_fmt_spec;
	int			i;

	i = 0;
	curr_fmt_spec = tinput->tfmt_spec;
	while (input_idx < ft_strlen(tinput->input_str))
	{
		i = 0;
		while ((input_idx < (size_t) curr_fmt_spec->start_idx
				|| input_idx > (size_t) curr_fmt_spec->end_idx)
			&& input_idx < ft_strlen(tinput->input_str))
			output_str[output_idx++] = tinput->input_str[input_idx++];
		while ((i < curr_fmt_spec->out_cont_len
				|| (curr_fmt_spec->start_idx == 0
					&& i < curr_fmt_spec->out_cont_len))
			&& input_idx < ft_strlen(tinput->input_str))
			output_str[output_idx++] = curr_fmt_spec->out_cont[i++];
		if (input_idx < ft_strlen(tinput->input_str))
			input_idx = curr_fmt_spec->end_idx + 1;
		if (curr_fmt_spec->next_fmt_spec)
			curr_fmt_spec = curr_fmt_spec->next_fmt_spec;
	}
	return (output_idx);
}

char	*wrap_up_the_string(t_input *tinput, char *output_str)
{
	size_t		input_idx;
	int			output_idx;

	input_idx = 0;
	output_idx = 0;
	tinput->output_str_len = fill_char_array(tinput, input_idx,
			output_idx, output_str);
	return (output_str);
}

char	*get_output_string(t_input *tinput, va_list var_args)
{
	t_fmt_spec	*fmt_spec;
	int			final_string_len;

	if (!(is_there_any_fmt_spec(tinput)))
		return (copy_input_str_and_exit(tinput));
	fmt_spec = tinput->tfmt_spec;
	while (fmt_spec)
	{
		if (flags_in_this_node(fmt_spec))
			resolve_flag_conflicts(fmt_spec);
		get_raw_string(fmt_spec, var_args);
		if (fmt_spec->out_cont == NULL)
			return (NULL);
		fmt_spec = fmt_spec->next_fmt_spec;
	}
	final_string_len = calculate_final_string_len(tinput);
	tinput->output_str = (char *) malloc(final_string_len + 1);
	if (!(tinput->output_str))
		return (NULL);
	tinput->output_str[final_string_len] = '\0';
	return (wrap_up_the_string(tinput, tinput->output_str));
}
