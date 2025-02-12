/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_logic_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:26:45 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flags_check(char character, t_fmt_spec *tfmt_spec)
{
	if (tfmt_spec->data_type == TYPE_PERCENT_SIGN)
		return ;
	if (character == '-')
		tfmt_spec->flags.alignment = 1;
	if (character == '.')
		tfmt_spec->flags.precision = 1;
	if (character == '#')
		tfmt_spec->flags.prefixe = 1;
	if (character == '+')
		tfmt_spec->flags.force_plus_sign = 1;
	if (character == ' ')
		tfmt_spec->flags.insert_space = 1;
}

static int	data_type_check(char character, t_fmt_spec *tfmt_spec)
{
	if (character == 'c')
		tfmt_spec->data_type = TYPE_CHAR;
	if (character == 's')
		tfmt_spec->data_type = TYPE_STRING;
	if (character == 'p')
		tfmt_spec->data_type = TYPE_POINTER;
	if (character == 'd')
		tfmt_spec->data_type = TYPE_INT;
	if (character == 'i')
		tfmt_spec->data_type = TYPE_EXPANDED_BASE_INT;
	if (character == 'u')
		tfmt_spec->data_type = TYPE_UNSIGNED_INT;
	if (character == 'x')
		tfmt_spec->data_type = TYPE_LOWER_HEX;
	if (character == 'X')
		tfmt_spec->data_type = TYPE_UPPER_HEX;
	if (character == '%')
		tfmt_spec->data_type = TYPE_PERCENT_SIGN;
	if (character == 'c' || character == 's' || character == 'p'
		|| character == 'd' || character == 'i' || character == 'u'
		|| character == 'x' || character == 'X' || character == '%')
		return (1);
	return (0);
}

int	determine_data_type(t_fmt_spec	*tfmt_spec, const char *string,
	int i)
{
	while (string[i])
	{
		if (data_type_check(string[i], tfmt_spec))
		{
			tfmt_spec->end_idx = i;
			tfmt_spec->orig_fmt_spec_str = ft_substr(
					string, tfmt_spec->start_idx,
					tfmt_spec->end_idx - tfmt_spec->start_idx + 1);
			if (!(tfmt_spec->orig_fmt_spec_str))
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	simplified_data_type_check(char character)
{
	if (character == 'c' || character == 's' || character == 'p'
		|| character == 'd' || character == 'i' || character == 'u'
		|| character == 'x' || character == 'X' || character == '%')
		return (1);
	return (0);
}

char	*copy_input_str_and_exit(t_input *tinput)
{
	tinput->output_str = ft_strdup(tinput->input_str);
	tinput->output_str_len = calculate_final_string_len(tinput);
	return (NULL);
}
