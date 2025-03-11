/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:59:04 by juhenriq          #+#    #+#             */
/*   Updated: 2025/03/10 22:18:28 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**get_splitted_line(t_map_reader_buffer *curr_map_line_read,
	t_map_reader_buffer *tmap_reader_buffer, t_map *map, int y)
{
	char	**splitted_map_line;

	splitted_map_line = ft_split(curr_map_line_read->line, ' ');
	if (!(splitted_map_line))
	{
		free_every_map_reader_node(tmap_reader_buffer);
		ft_printf("Split function failed.\n");
		exit(1);
	}
	map->dots[y] = (t_map_dots *)
		malloc((map->max_x_coordinate_recorded + 1) * sizeof(t_map_dots));
	if (!(map->dots[y]))
	{
		free_every_map_reader_node(tmap_reader_buffer);
		free_map(map);
		ft_printf("Malloc failed.\n");
		exit(1);
	}
	return (splitted_map_line);
}

unsigned int	get_color_from_dot(char *str)
{
	int			str_start_idx;
	int			str_end_idx;
	char		*extracted_color_str;
	long long	extracted_color;
	int			i;

	if (find_char(str, ',', 0) == -1)
		return (0);
	str_start_idx = find_char(str, ',', 0) + 1;
	i = str_start_idx;
	while (str[i] && str[i] != ' ')
		i++;
	if (i > 8 + str_start_idx)
		return ((unsigned int) 0);
	str_end_idx = i - 1;
	extracted_color_str = ft_substr(str, str_start_idx + 2,
			str_end_idx - str_start_idx + 1);
	if (hex_str_to_long_long(extracted_color_str, &extracted_color) == -1)
	{
		ft_printf("Invalid hex parameter as color. Exiting the program.");
		return ((unsigned int) 0);
	}
	return ((unsigned int) extracted_color);
}

int	get_z_coordinate_from_dot(char *str)
{
	char			*extracted_str;
	unsigned int	z_value;

	extracted_str = ft_substr(str, 0, (find_char(str, ',', 0) - 1));
	z_value = ft_atoi(extracted_str);
	free(extracted_str);
	return (z_value);
}

void	get_max_cordinates_loop_condition(
	t_map_reader_buffer *curr_reader_buffer, int *nb_detected, int *nb_of_dots,
	int i)
{
	if (curr_reader_buffer->line[i] == ' '
		|| curr_reader_buffer->line[i] == '\n')
		*nb_detected = 0;
	else
	{
		if (*nb_detected == 0)
			(*nb_of_dots)++;
		*nb_detected = 1;
	}
}

void	get_max_cordinates(t_map *map,
	t_map_reader_buffer *tmap_reader_buffer)
{
	t_map_reader_buffer	*curr_reader_buffer;
	int					nb_of_dots;
	int					nb_detected;
	int					i;

	map->max_x_coordinate_recorded = 0;
	map->max_y_coordinate_recorded = 0;
	curr_reader_buffer = tmap_reader_buffer;
	while (curr_reader_buffer)
	{
		nb_detected = 0;
		nb_of_dots = 0;
		i = -1;
		while (curr_reader_buffer->line[++i])
			get_max_cordinates_loop_condition(curr_reader_buffer,
				&nb_detected, &nb_of_dots, i);
		if (map->max_x_coordinate_recorded < nb_of_dots)
			map->max_x_coordinate_recorded = nb_of_dots - 1;
		curr_reader_buffer = curr_reader_buffer->next_line_buffer;
		map->max_y_coordinate_recorded++;
	}
	map->max_y_coordinate_recorded--;
}
