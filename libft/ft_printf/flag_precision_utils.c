/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_precision_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:33:37 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/01 04:29:36 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_return_an_empty_str(t_fmt_spec *tfmt_spec)
{
	free(tfmt_spec->out_cont);
	tfmt_spec->out_cont = ft_strdup("");
	tfmt_spec->out_cont_len = 0;
}

char	*ft_printf_create_new_str(t_fmt_spec *tfmt_spec, int char_limiter)
{
	char	*new_str;

	new_str = (char *) malloc(tfmt_spec->out_cont_len + char_limiter + 1);
	if (!(new_str))
	{
		free(tfmt_spec->out_cont);
		free(tfmt_spec->out_cont = NULL);
		return (NULL);
	}
	new_str[tfmt_spec->out_cont_len + char_limiter] = '\0';
	return (new_str);
}

void	return_out_str_as_usual(t_fmt_spec *tfmt_spec, char *new_str)
{
	free(tfmt_spec->out_cont);
	tfmt_spec->out_cont = new_str;
	tfmt_spec->out_cont_len = ft_strlen(tfmt_spec->out_cont);
}

static char	*pointer_exception_fill_new_str(char *new_str,
	char *ptr_addr_as_str, int new_str_len, int add_zeros)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	while (i < new_str_len)
	{
		while (i > 1 && add_zeros > 0)
		{
			new_str[i++] = '0';
			add_zeros--;
		}
		if (i > 1)
			new_str[i] = ptr_addr_as_str[j++];
		i++;
	}
	return (new_str);
}

char	*pointer_exception_work_on_out_string(t_fmt_spec *tfmt_spec,
	int new_str_len, int add_zeros, char *ptr_addr_as_str)
{
	char	*new_str;

	new_str = (char *) malloc(new_str_len + 1);
	if (!(new_str))
	{
		free(tfmt_spec->out_cont);
		tfmt_spec->out_cont = NULL;
		return (NULL);
	}
	new_str[new_str_len] = '\0';
	new_str[0] = '0';
	new_str[1] = 'x';
	return (pointer_exception_fill_new_str(new_str, ptr_addr_as_str,
			new_str_len, add_zeros));
}
