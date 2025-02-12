/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:24:01 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/06 03:14:30 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_free_everything(t_input **input_str)
{
	t_fmt_spec	*curr_fmt_spec;
	t_fmt_spec	*next_fmt_spec;

	if (!(*input_str))
		return (-1);
	curr_fmt_spec = (*input_str)->tfmt_spec;
	while (curr_fmt_spec)
	{
		next_fmt_spec = curr_fmt_spec->next_fmt_spec;
		free(curr_fmt_spec->out_cont);
		free(curr_fmt_spec->orig_fmt_spec_str);
		free(curr_fmt_spec);
		curr_fmt_spec = next_fmt_spec;
	}
	free((*input_str)->output_str);
	free(*input_str);
	*input_str = NULL;
	return (-1);
}

char	*ft_printf_modified_ft_strdup(char *str, unsigned long max_idx)
{
	char				*output_string;
	unsigned long		i;

	output_string = malloc(max_idx + 1);
	if (!(output_string))
		return (NULL);
	output_string[max_idx] = '\0';
	i = 0;
	while (i <= max_idx)
	{
		output_string[i] = str[i];
		i++;
	}
	return (output_string);
}

t_fmt_spec	*create_fmt_specifier(int fmt_start_idx)
{
	t_fmt_spec	*newest_fmt_node;

	newest_fmt_node = (t_fmt_spec *) malloc(sizeof(t_fmt_spec));
	if (!(newest_fmt_node))
		return (NULL);
	newest_fmt_node->start_idx = fmt_start_idx;
	newest_fmt_node->out_cont = NULL;
	newest_fmt_node->orig_fmt_spec_str = NULL;
	newest_fmt_node->next_fmt_spec = NULL;
	newest_fmt_node->out_cont_len = -1;
	newest_fmt_node->flags.alignment = 0;
	newest_fmt_node->flags.fill_zero = 0;
	newest_fmt_node->flags.precision = 0;
	newest_fmt_node->flags.prefixe = 0;
	newest_fmt_node->flags.force_plus_sign = 0;
	newest_fmt_node->flags.insert_space = 0;
	newest_fmt_node->flags.field_width = 0;
	return (newest_fmt_node);
}

int	find_char(const char *str, char target_char, int start_idx)
{
	size_t	i;
	size_t	local_start;

	if (!(str) || start_idx < 0)
		return (-1);
	local_start = (size_t) start_idx;
	if (local_start > ft_strlen(str) - 1)
		return (-1);
	i = local_start;
	while (str[i])
	{
		if (str[i] == target_char)
			return (i);
		i++;
	}
	return (-1);
}

t_input	*create_tinput_str(const char *string)
{
	t_input	*tinput_str;

	tinput_str = malloc(sizeof(t_input));
	if (!(tinput_str))
		return (NULL);
	tinput_str->input_str = string;
	tinput_str->output_str = NULL;
	tinput_str->tfmt_spec = NULL;
	tinput_str->output_str_len = 0;
	if (identify_specifiers(tinput_str))
		return (NULL);
	return (tinput_str);
}
