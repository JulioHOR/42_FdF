/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:34:09 by juhenriq          #+#    #+#             */
/*   Updated: 2025/02/06 03:14:30 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include "../libft.h"

typedef enum e_data_type
{
	TYPE_CHAR,
	TYPE_STRING,
	TYPE_POINTER,
	TYPE_INT,
	TYPE_EXPANDED_BASE_INT,
	TYPE_UNSIGNED_INT,
	TYPE_LOWER_HEX,
	TYPE_UPPER_HEX,
	TYPE_PERCENT_SIGN
}	t_data_type;

typedef struct s_flags
{
	int	alignment;
	int	fill_zero;
	int	precision;
	int	prefixe;
	int	force_plus_sign;
	int	insert_space;
	int	field_width;
}	t_flags;

typedef struct s_fmt_spec
{
	t_data_type			data_type;
	t_flags				flags;
	int					start_idx;
	int					end_idx;
	char				*orig_fmt_spec_str;
	char				*out_cont;
	int					out_cont_len;
	struct s_fmt_spec	*next_fmt_spec;
}	t_fmt_spec;

typedef struct s_input
{
	const char		*input_str;
	char			*output_str;
	int				output_str_len;
	t_fmt_spec		*tfmt_spec;
}	t_input;

char		*copy_input_str_and_exit(t_input *tinput);
char		*ft_printf_create_new_str(t_fmt_spec *tfmt_spec, int char_limiter);
char		*get_output_string(t_input *tinput_str, va_list va_args);
char		*ft_printf_modified_ft_strdup(char *str, unsigned long max_idx);
char		*pointer_exception_work_on_out_string(t_fmt_spec *tfmt_spec,
				int new_str_len, int add_zeros, char *ptr_addr_as_str);
char		*unsigned_hex_int_to_hex(unsigned int number, int case_flag);
char		*unsigned_ptr_int_to_hex(uint64_t number, int case_flag);
int			calculate_final_string_len(t_input *tinput_str);
int			contains_nil(char *str);
int			determine_data_type(t_fmt_spec *tfmt_spec, const char *string,
				int i);
int			find_char(const char *str, char target_char, int start);
int			flags_in_this_node(t_fmt_spec *tfmt_spec);
int			ft_printf(const char *string, ...);
int			ft_printf_free_everything(t_input **tinput_str);
int			get_ptr_modifier(t_fmt_spec *tfmt_spec);
int			identify_specifiers(t_input *tinput_str);
int			is_there_any_fmt_spec(t_input *tinput_str);
int			simplified_data_type_check(char character);
t_fmt_spec	*create_fmt_specifier(int fmt_start_idx);
t_input		*create_tinput_str(const char *string);
void		alignment_flag_applier(t_fmt_spec *tfmt_spec);
void		fill_zero_flag_applier(t_fmt_spec *tfmt_spec);
void		flags_check(char character, t_fmt_spec *tfmt_spec);
void		flags_part(t_fmt_spec *tfmt_spec);
void		force_plus_sign_flag_applier(t_fmt_spec *tfmt_spec);
void		ft_printf_return_an_empty_str(t_fmt_spec *tfmt_spec);
void		get_raw_string(t_fmt_spec *tfmt_spec, va_list var_args);
void		insert_spaces_flag_applier(t_fmt_spec *tfmt_spec);
void		precision_flag_applier(t_fmt_spec *tfmt_spec);
void		prefixe_flag_applier(t_fmt_spec *tfmt_spec);
void		raw_content_part(t_fmt_spec *tfmt_spec, va_list var_args);
void		return_out_str_as_usual(t_fmt_spec *tfmt_spec, char *new_str);
void		to_string_char(t_fmt_spec *tfmt_spec, char c);
void		to_string_hex(t_fmt_spec *tfmt_spec, uint64_t nb, int case_flag,
				int hex_or_ptr);
void		to_string_int(t_fmt_spec *tfmt_spec, int integer);
void		to_string_percent(t_fmt_spec *tfmt_spec);
void		to_string_pointer(t_fmt_spec *tfmt_spec, void *ptr, int hex_or_ptr);
void		to_string_string(t_fmt_spec *tfmt_spec, char *str);
void		to_string_unsigned_int(t_fmt_spec *tfmt_spec, unsigned int n);
void		width_flag_applier(t_fmt_spec *tfmt_spec);
void		width_flag_checker(t_fmt_spec *tfmt_spec);

#endif