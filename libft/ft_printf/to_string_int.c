/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:00:34 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	to_string_int(t_fmt_spec *tfmt_spec, int integer)
{
	tfmt_spec->out_cont = (ft_itoa(integer));
}
