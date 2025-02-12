/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_string_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:35:42 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_nb_of_fmt_spec_nodes(t_fmt_spec *tfmt_spec)
{
	int	i;

	if (!(tfmt_spec))
		return (0);
	i = 1;
	while (tfmt_spec)
	{
		tfmt_spec = tfmt_spec->next_fmt_spec;
		i++;
	}
	return (i);
}

int	flags_in_this_node(t_fmt_spec *tfmt_spec)
{
	t_flags	*flags;

	flags = &(tfmt_spec->flags);
	if (flags->alignment || flags->fill_zero || flags->precision
		|| flags->prefixe || flags->force_plus_sign || flags->insert_space)
		return (1);
	return (0);
}

int	is_there_any_fmt_spec(t_input *tinput_str)
{
	if (get_nb_of_fmt_spec_nodes(tinput_str->tfmt_spec) > 0)
		return (1);
	else
		return (0);
}

int	calculate_final_string_len(t_input *tinput_str)
{
	t_fmt_spec	*curr_tfmt_spec;
	int			total_content_len;
	int			minus_spec_idxs;

	total_content_len = 0;
	minus_spec_idxs = 0;
	curr_tfmt_spec = tinput_str->tfmt_spec;
	while (curr_tfmt_spec)
	{
		total_content_len += curr_tfmt_spec->out_cont_len;
		minus_spec_idxs += 1 + curr_tfmt_spec->end_idx
			- curr_tfmt_spec->start_idx;
		curr_tfmt_spec = curr_tfmt_spec->next_fmt_spec;
	}
	return (ft_strlen(tinput_str->input_str)
		+ total_content_len - minus_spec_idxs);
}

void	get_raw_string(t_fmt_spec *tfmt_spec, va_list var_args)
{
	raw_content_part(tfmt_spec, var_args);
	flags_part(tfmt_spec);
	if (tfmt_spec->out_cont[0] != '\0' && tfmt_spec->flags.field_width != 1)
		tfmt_spec->out_cont_len = ft_strlen(tfmt_spec->out_cont);
}
