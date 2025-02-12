/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:11:18 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	to_string_percent(t_fmt_spec *tfmt_spec)
{
	char	*percent_str;

	percent_str = (char *) malloc(2);
	if (!(percent_str))
		tfmt_spec->out_cont = percent_str;
	percent_str[0] = '%';
	percent_str[1] = '\0';
	tfmt_spec->out_cont = percent_str;
}
