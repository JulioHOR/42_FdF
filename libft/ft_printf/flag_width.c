/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_width.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:25:27 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	flag_width_fill_str(t_fmt_spec *tfmt_spec, char *applied_str,
	int nb_to_apply_width_as_int)
{
	int	len_difference;
	int	i;
	int	j;

	len_difference = nb_to_apply_width_as_int - tfmt_spec->out_cont_len;
	i = 0;
	j = 0;
	while (i < nb_to_apply_width_as_int)
	{
		if (i < len_difference)
			applied_str[i] = ' ';
		else
			applied_str[i] = tfmt_spec->out_cont[j++];
		i++;
	}
}

static void	width_applied_str(int nb_to_apply_width_as_int,
	t_fmt_spec *tfmt_spec)
{
	char	*applied_str;

	if (nb_to_apply_width_as_int < tfmt_spec->out_cont_len)
		return ;
	applied_str = (char *) malloc(nb_to_apply_width_as_int + 1);
	if (!(applied_str))
	{
		free(tfmt_spec->out_cont);
		tfmt_spec->out_cont = NULL;
		return ;
	}
	applied_str[nb_to_apply_width_as_int] = '\0';
	flag_width_fill_str(tfmt_spec, applied_str, nb_to_apply_width_as_int);
	free(tfmt_spec->out_cont);
	tfmt_spec->out_cont = applied_str;
	tfmt_spec->out_cont_len = nb_to_apply_width_as_int;
}

void	width_flag_applier(t_fmt_spec *tfmt_spec)
{
	int		i;
	int		nb_to_apply_width_as_int;
	int		digit_active;

	nb_to_apply_width_as_int = 0;
	digit_active = 0;
	i = 1;
	while (tfmt_spec->orig_fmt_spec_str[i])
	{
		if (ft_isdigit(tfmt_spec->orig_fmt_spec_str[i]))
		{
			digit_active = 1;
			nb_to_apply_width_as_int = ft_atoi(
					&(tfmt_spec->orig_fmt_spec_str[i]));
			break ;
		}
		i++;
	}
	if (nb_to_apply_width_as_int <= 0 || !(digit_active))
		return ;
	width_applied_str(nb_to_apply_width_as_int, tfmt_spec);
}

void	width_flag_checker(t_fmt_spec *tfmt_spec)
{
	char	*tfmt_str;
	int		zero_before_digit;
	int		i;

	zero_before_digit = 1;
	tfmt_str = tfmt_spec->orig_fmt_spec_str;
	i = 1;
	while (tfmt_str[i])
	{
		if (tfmt_str[i] == '.')
			break ;
		if (ft_isdigit(tfmt_str[i]) && tfmt_str[i] != '0')
			zero_before_digit = 0;
		if (tfmt_str[i] == '0' && zero_before_digit == 1
			&& tfmt_spec->data_type != TYPE_CHAR
			&& tfmt_spec->data_type != TYPE_STRING)
			tfmt_spec->flags.fill_zero = 1;
		if (ft_isdigit(tfmt_str[i])
			&& tfmt_spec->flags.fill_zero != 1
			&& tfmt_spec->flags.alignment != 1
			&& tfmt_spec->data_type != TYPE_PERCENT_SIGN)
			tfmt_spec->flags.field_width = 1;
		i++;
	}
}
