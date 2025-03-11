/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:56:58 by juhenriq          #+#    #+#             */
/*   Updated: 2025/03/10 22:18:28 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	load_map_lines(t_map_reader_buffer **tmap_reader_buffer, int fd)
{
	char				*temp_line;
	t_map_reader_buffer	*last_map_line_read;
	t_map_reader_buffer	*curr_map_line_read;

	last_map_line_read = NULL;
	while (1)
	{
		temp_line = get_next_line(fd);
		if (!(temp_line))
			break ;
		curr_map_line_read = ((t_map_reader_buffer *)
				malloc(sizeof(t_map_reader_buffer)));
		if (!(curr_map_line_read))
		{
			free_every_map_reader_node(*tmap_reader_buffer);
			ft_printf("Malloc failure when reading the map file.");
		}
		if (last_map_line_read)
			last_map_line_read->next_line_buffer = curr_map_line_read;
		if (!(*tmap_reader_buffer))
			*tmap_reader_buffer = curr_map_line_read;
		curr_map_line_read->line = temp_line;
		curr_map_line_read->next_line_buffer = NULL;
		last_map_line_read = curr_map_line_read;
	}
}

void	map_creator(t_map *map, t_map_reader_buffer	*tmap_reader_buffer)
{
	map->dots = (t_map_dots **) malloc((map->max_y_coordinate_recorded + 1)
			* sizeof(t_map_dots *));
	if (!(map->dots))
	{
		free_every_map_reader_node(tmap_reader_buffer);
		exit(1);
	}
}

void	free_every_map_reader_node(t_map_reader_buffer *tmap_reader_buffer)
{
	t_map_reader_buffer	*temp_ptr;

	while (tmap_reader_buffer)
	{
		free(tmap_reader_buffer->line);
		temp_ptr = tmap_reader_buffer;
		tmap_reader_buffer = tmap_reader_buffer->next_line_buffer;
		free(temp_ptr);
	}
}

void	free_map(t_map *map)
{
	int	y;

	y = 0;
	while (y <= map->max_y_coordinate_recorded)
		if (map->dots[y])
			free(map->dots[y++]);
	free(map->dots);
}
