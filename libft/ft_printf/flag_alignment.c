/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_alignment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:46:43 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	work_on_output_str(t_fmt_spec *tfmt_spec, int alignment_nb,
	int alignment_to_apply, int insert_spaces_modifier)
{
	char	*new_content;
	int		i;

	new_content = (char *) malloc(tfmt_spec->out_cont_len
			+ alignment_to_apply + 1);
	if (!(new_content))
	{
		free(tfmt_spec->out_cont);
		tfmt_spec->out_cont = NULL;
		return ;
	}
	new_content[tfmt_spec->out_cont_len + alignment_to_apply] = '\0';
	ft_memcpy(new_content, tfmt_spec->out_cont, tfmt_spec->out_cont_len);
	i = tfmt_spec->out_cont_len;
	while (i < alignment_nb - insert_spaces_modifier)
	{
		new_content[i] = ' ';
		i++;
	}
	free(tfmt_spec->out_cont);
	tfmt_spec->out_cont = new_content;
	if (tfmt_spec->out_cont[0] == '\0' && tfmt_spec->data_type == TYPE_CHAR)
		tfmt_spec->out_cont_len = tfmt_spec->out_cont_len + alignment_to_apply;
	else
		tfmt_spec->out_cont_len = ft_strlen(tfmt_spec->out_cont);
}

static int	get_alignment_nb(t_fmt_spec *tfmt_spec, int minus_idx)
{
	int	alignment_nb;

	if (tfmt_spec->data_type == TYPE_CHAR
		&& tfmt_spec->flags.force_plus_sign == -1)
		alignment_nb = ft_atoi((const char *)
				&(tfmt_spec->orig_fmt_spec_str[
					find_char(tfmt_spec->orig_fmt_spec_str, '+', 1) + 1]));
	else
		alignment_nb = ft_atoi((const char *)
				&(tfmt_spec->orig_fmt_spec_str[minus_idx + 1]));
	return (alignment_nb);
}

static int	get_last_minux_idx(t_fmt_spec *tfmt_spec)
{
	int	minus_idx;
	int	orig_spec_last_idx;
	int	temp;

	temp = 0;
	minus_idx = 0;
	while (temp != -1)
	{
		temp = find_char(tfmt_spec->orig_fmt_spec_str, '-', minus_idx + 1);
		if (temp != -1)
			minus_idx = temp;
	}
	orig_spec_last_idx = (ft_strlen(tfmt_spec->orig_fmt_spec_str) - 1);
	while ((minus_idx + 1) <= orig_spec_last_idx
		&& !(ft_isdigit(tfmt_spec->orig_fmt_spec_str[minus_idx + 1]))
		&& tfmt_spec->orig_fmt_spec_str[minus_idx + 1] != '.')
		minus_idx++;
	return (minus_idx);
}

void	alignment_flag_applier(t_fmt_spec *tfmt_spec)
{
	int		alignment_nb;
	int		alignment_to_apply;
	int		minus_idx;
	int		insert_spaces_modifier;

	minus_idx = get_last_minux_idx(tfmt_spec);
	alignment_nb = get_alignment_nb(tfmt_spec, minus_idx);
	if (tfmt_spec->flags.insert_space == 1
		&& ft_atoi(tfmt_spec->out_cont) >= 0
		&& ft_strcmp_homemade("(nil)", tfmt_spec->out_cont))
		insert_spaces_modifier = 1;
	else
		insert_spaces_modifier = 0;
	alignment_to_apply = alignment_nb - tfmt_spec->out_cont_len
		- insert_spaces_modifier;
	if (alignment_to_apply <= 0)
		return ;
	work_on_output_str(tfmt_spec, alignment_nb, alignment_to_apply,
		insert_spaces_modifier);
}
