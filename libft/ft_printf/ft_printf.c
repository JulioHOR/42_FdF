/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:29:08 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/06 03:14:30 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	determine_flags(t_fmt_spec	*tfmt_spec, const char *string, int i)
{
	while (string[i])
	{
		flags_check(string[i], tfmt_spec);
		if (simplified_data_type_check(string[i]))
		{
			width_flag_checker(tfmt_spec);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	add_last_tfmt_spec_node(t_input *tinput_str, t_fmt_spec *tfmt_spec)
{
	t_fmt_spec	*curr_fmt_node;
	t_fmt_spec	*last_fmt_node;

	last_fmt_node = NULL;
	curr_fmt_node = tinput_str->tfmt_spec;
	while (curr_fmt_node)
	{
		last_fmt_node = curr_fmt_node;
		curr_fmt_node = curr_fmt_node->next_fmt_spec;
	}
	if (!(last_fmt_node))
		tinput_str->tfmt_spec = tfmt_spec;
	else
		last_fmt_node->next_fmt_spec = tfmt_spec;
}

int	identify_specifiers(t_input *tinput_str)
{
	const char	*string;
	int			fmt_spec_idx;
	t_fmt_spec	*tfmt_spec;

	string = tinput_str->input_str;
	fmt_spec_idx = find_char(string, '%', 0);
	while (fmt_spec_idx != -1)
	{
		tfmt_spec = create_fmt_specifier(fmt_spec_idx);
		if (!(tfmt_spec))
			return (1);
		if (determine_data_type(tfmt_spec, string, fmt_spec_idx + 1))
			return (1);
		if (determine_flags(tfmt_spec, string, fmt_spec_idx + 1))
			return (1);
		add_last_tfmt_spec_node(tinput_str, tfmt_spec);
		if (tfmt_spec->data_type == TYPE_PERCENT_SIGN)
			fmt_spec_idx = find_char(string, '%', (tfmt_spec->end_idx + 1));
		else
			fmt_spec_idx = find_char(string, '%', fmt_spec_idx + 1);
	}
	return (0);
}

int	ft_printf(const char *input_str, ...)
{
	va_list		var_args;
	t_input		*tinput_str;
	char		*output_string;
	int			final_str_len;

	va_start(var_args, input_str);
	if (!(input_str))
		return (-1);
	tinput_str = create_tinput_str(input_str);
	if (!(tinput_str))
		return (ft_printf_free_everything(&tinput_str));
	get_output_string(tinput_str, var_args);
	output_string = ft_printf_modified_ft_strdup(tinput_str->output_str,
			tinput_str->output_str_len);
	if (!(output_string))
	{
		ft_printf_free_everything(&tinput_str);
		return (-1);
	}
	final_str_len = tinput_str->output_str_len;
	write(1, output_string, tinput_str->output_str_len);
	free(output_string);
	ft_printf_free_everything(&tinput_str);
	va_end(var_args);
	return (final_str_len);
}
