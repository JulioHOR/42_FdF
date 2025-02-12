/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_fill_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 02:26:42 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	finalize_fill_zero_str(t_fmt_spec *tfmt_spec, char *new_str)
{
	free(tfmt_spec->out_cont);
	if (tfmt_spec->data_type == TYPE_POINTER)
	{
		tfmt_spec->out_cont = ft_strjoin("0x", new_str);
		free(new_str);
	}
	else
		tfmt_spec->out_cont = new_str;
}

static void	work_on_output_str(t_fmt_spec *tfmt_spec, int zeroes_to_apply,
	int ptr_modifier, char *new_str)
{
	int	i;
	int	j;

	i = -1;
	j = ptr_modifier;
	if (tfmt_spec->out_cont[0] == '-')
	{
		new_str[0] = '-';
		zeroes_to_apply++;
		i++;
		j++;
	}
	while (++i < zeroes_to_apply + tfmt_spec->out_cont_len - ptr_modifier)
	{
		if (i < zeroes_to_apply)
			new_str[i] = '0';
		else
			new_str[i] = tfmt_spec->out_cont[j++];
	}
	finalize_fill_zero_str(tfmt_spec, new_str);
}

static int	nil_and_precision_exceptions(t_fmt_spec *tfmt_spec)
{
	if (!(ft_strcmp_homemade("(nil)", tfmt_spec->out_cont))
		|| tfmt_spec->flags.precision == 1)
	{
		tfmt_spec->flags.field_width = 1;
		return (1);
	}
	return (0);
}

static char	*get_new_string(t_fmt_spec *tfmt_spec, int zeroes_to_apply,
	int ptr_modifier)
{
	char	*new_str;

	new_str = (char *) malloc(tfmt_spec->out_cont_len + zeroes_to_apply
			- ptr_modifier + 1);
	if (!(new_str))
	{
		free(tfmt_spec->out_cont);
		tfmt_spec->out_cont = NULL;
		return (NULL);
	}
	new_str[tfmt_spec->out_cont_len + zeroes_to_apply - ptr_modifier] = '\0';
	return (new_str);
}

void	fill_zero_flag_applier(t_fmt_spec *tfmt_spec)
{
	char	*new_str;
	int		zeroes_to_apply;
	int		ptr_modifier;

	if (nil_and_precision_exceptions(tfmt_spec))
		return ;
	zeroes_to_apply = ft_atoi(&(tfmt_spec->orig_fmt_spec_str[1]))
		- tfmt_spec->out_cont_len;
	if (zeroes_to_apply < 1)
		return ;
	ptr_modifier = get_ptr_modifier(tfmt_spec);
	new_str = get_new_string(tfmt_spec, zeroes_to_apply, ptr_modifier);
	if (!(new_str))
		return ;
	work_on_output_str(tfmt_spec, zeroes_to_apply, ptr_modifier, new_str);
}
