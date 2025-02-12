/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_precision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 02:27:17 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pointer_exception(t_fmt_spec *tfmt_spec, int char_limiter)
{
	char	*ptr_addr_as_str;
	int		ptr_addr_len;
	int		last_char_prefixe_idx;
	char	*new_str;
	int		add_zeros;

	if (contains_nil(tfmt_spec->out_cont))
		return ;
	last_char_prefixe_idx = find_char(tfmt_spec->out_cont, 'x', 0);
	ptr_addr_as_str = ft_substr(
			tfmt_spec->out_cont, last_char_prefixe_idx + 1,
			tfmt_spec->out_cont_len - last_char_prefixe_idx);
	ptr_addr_len = ft_strlen(ptr_addr_as_str);
	if (char_limiter <= ptr_addr_len)
		return ;
	add_zeros = 0;
	if (char_limiter > ptr_addr_len)
		add_zeros = char_limiter - ptr_addr_len;
	new_str = pointer_exception_work_on_out_string(tfmt_spec, char_limiter + 2,
			add_zeros, ptr_addr_as_str);
	if (!(new_str))
		return ;
	return_out_str_as_usual(tfmt_spec, new_str);
}

static void	second_half_not_string_case(t_fmt_spec *tfmt_spec,
	int char_limiter, int minus_found, char	*new_str)
{
	int	i;
	int	j;

	if (minus_found)
	{
		new_str[0] = '-';
		i = 1;
		j = 1;
	}
	else
	{
		i = 0;
		j = 0;
	}
	while (i < (tfmt_spec->out_cont_len + char_limiter))
	{
		if (i < char_limiter + minus_found)
			new_str[i] = '0';
		else
			new_str[i] = tfmt_spec->out_cont[j++];
		i++;
	}
	return_out_str_as_usual(tfmt_spec, new_str);
}

static void	first_half_not_string_case(t_fmt_spec *tfmt_spec, int char_limiter)
{
	char	*new_str;
	int		minus_found;

	if (tfmt_spec->data_type == TYPE_POINTER)
		return (pointer_exception(tfmt_spec, char_limiter));
	if (char_limiter == 0 && tfmt_spec->out_cont
		&& tfmt_spec->out_cont[0] == '0'
		&& tfmt_spec->data_type != TYPE_POINTER)
		ft_printf_return_an_empty_str(tfmt_spec);
	if (char_limiter == 0 && tfmt_spec->data_type != TYPE_POINTER)
		return ;
	if (find_char(tfmt_spec->out_cont, '-', 0) != -1)
		minus_found = 1;
	else
		minus_found = 0;
	if (char_limiter <= tfmt_spec->out_cont_len - minus_found)
		return ;
	char_limiter -= tfmt_spec->out_cont_len - minus_found;
	new_str = ft_printf_create_new_str(tfmt_spec, char_limiter);
	if (!(new_str))
		return ;
	second_half_not_string_case(tfmt_spec, char_limiter, minus_found, new_str);
}

static void	string_case(t_fmt_spec *tfmt_spec, int char_limiter)
{
	char	*new_str;

	if (char_limiter >= tfmt_spec->out_cont_len
		|| tfmt_spec->out_cont_len == 0)
		return ;
	if (char_limiter == 0)
	{
		tfmt_spec->out_cont[0] = '\0';
		tfmt_spec->out_cont_len = 0;
		return ;
	}
	new_str = ft_substr(tfmt_spec->out_cont, 0, char_limiter);
	free(tfmt_spec->out_cont);
	tfmt_spec->out_cont = new_str;
	tfmt_spec->out_cont_len = ft_strlen(tfmt_spec->out_cont);
}

void	precision_flag_applier(t_fmt_spec *tfmt_spec)
{
	int	char_limiter;
	int	dot_idx;

	dot_idx = find_char(tfmt_spec->orig_fmt_spec_str, '.', 0);
	char_limiter = ft_atoi(&(tfmt_spec->orig_fmt_spec_str[dot_idx + 1]));
	if (!(ft_strcmp_homemade("(null)", tfmt_spec->out_cont)))
	{
		if (char_limiter >= 6)
			return ;
		else
			return (ft_printf_return_an_empty_str(tfmt_spec));
	}
	if (tfmt_spec->data_type == TYPE_STRING)
		string_case(tfmt_spec, char_limiter);
	else
		first_half_not_string_case(tfmt_spec, char_limiter);
}
