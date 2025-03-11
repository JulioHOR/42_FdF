/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:54:03 by juhenriq          #+#    #+#             */
/*   Updated: 2025/03/10 22:35:37 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	map_text_parser(const char *map_name,
	t_map_reader_buffer **tmap_reader_buffer)
{
	int					fd;
	char				*map_name_full_path;

	map_name_full_path = ft_strjoin("maps/", map_name);
	fd = open(map_name_full_path, O_RDONLY);
	free(map_name_full_path);
	map_name_full_path = NULL;
	if (fd == -1)
	{
		ft_printf("Could not find the map in the \"maps\" folder. Are you sure "
			"it's there?");
		exit(1);
	}
	*tmap_reader_buffer = NULL;
	load_map_lines(tmap_reader_buffer, fd);
	if (!(tmap_reader_buffer))
	{
		ft_printf("An empty map was provided... And this is not valid.");
		exit(1);
	}
}

static void	map_loader_main_loop(t_map *map, int *y, int *end_of_line_reached,
	char **splitted_map_line)
{
	int	x;

	x = -1;
	*end_of_line_reached = 0;
	while (++x <= map->max_x_coordinate_recorded)
	{
		map->dots[*y][x].x_coordinate = x;
		map->dots[*y][x].y_coordinate = *y;
		if (*end_of_line_reached || splitted_map_line[x] == NULL
			|| splitted_map_line[x][0] == '\n')
			*end_of_line_reached = 1;
		if (*end_of_line_reached)
		{
			map->dots[*y][x].z_coordinate = 0;
			map->dots[*y][x].color = 0;
		}
		else
		{
			map->dots[*y][x].color = get_color_from_dot(splitted_map_line[x]);
			map->dots[*y][x].z_coordinate = get_z_coordinate_from_dot(
					splitted_map_line[x]);
		}
	}
}

static void	load_map_line_by_line(t_map_reader_buffer *curr_map_line_read,
	t_map_reader_buffer *tmap_reader_buffer, t_map *map)
{
	char	**splitted_map_line;
	int		end_of_line_reached;
	int		y;
	int		i;

	y = 0;
	while (curr_map_line_read)
	{
		splitted_map_line = get_splitted_line(curr_map_line_read,
				tmap_reader_buffer, map, y);
		map_loader_main_loop(map, &y, &end_of_line_reached, splitted_map_line);
		i = 0;
		while (splitted_map_line[i])
			free(splitted_map_line[i++]);
		free(splitted_map_line);
		splitted_map_line = NULL;
		y++;
		curr_map_line_read = curr_map_line_read->next_line_buffer;
	}
}

t_map	load_map(const char *map_name)
{
	t_map_reader_buffer	*tmap_reader_buffer;
	t_map_reader_buffer	*curr_map_line_read;
	t_map				map;

	map_text_parser(map_name, &tmap_reader_buffer);
	get_max_cordinates(&map, tmap_reader_buffer);
	if (map.max_x_coordinate_recorded == 0
		|| map.max_y_coordinate_recorded == 0)
	{
		ft_printf("This should never happen! Max x or y were found to be 0");
		free_every_map_reader_node(tmap_reader_buffer);
		exit(1);
	}
	map_creator(&map, tmap_reader_buffer);
	curr_map_line_read = tmap_reader_buffer;
	load_map_line_by_line(curr_map_line_read, tmap_reader_buffer, &map);
	free_every_map_reader_node(tmap_reader_buffer);
	return (map);
}
