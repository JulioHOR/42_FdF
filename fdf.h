/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 04:04:13 by juhenriq          #+#    #+#             */
/*   Updated: 2025/03/10 23:04:05 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

# define WHITE 0xFFFFFFFF

typedef struct s_map_dots
{
	int				x_coordinate;
	int				y_coordinate;
	int				z_coordinate;
	unsigned int	color;
}	t_map_dots;

typedef struct s_draw_targets
{
	int				x0;
	int				x1;
	int				y0;
	int				y1;
	unsigned int	color_0;
	unsigned int	color_1;
}	t_draw_targets;

typedef struct s_map
{
	t_map_dots	**dots;
	int			max_x_coordinate_recorded;
	int			max_y_coordinate_recorded;
}	t_map;

typedef struct s_fdf
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			*map;
	int				zoom_level;
	double			scale_factor;
	int				x_window_size;
	int				y_window_size;
	int				x_center;
	int				y_center;
}	t_fdf;

typedef struct s_map_reader_buffer
{
	char						*line;
	struct s_map_reader_buffer	*next_line_buffer;
}	t_map_reader_buffer;

void			draw_background(t_fdf *fdf);
void			draw_line(mlx_image_t *img, t_draw_targets *tdraw_targets);
void			draw_points(void *fdf_ptr);
void			free_every_map_reader_node(
					t_map_reader_buffer *tmap_reader_buffer);
void			free_map(t_map *map);
int				first_and_last_pixels_validator(t_draw_targets *tdraw_targets,
					mlx_image_t *img);
void			get_max_cordinates(t_map *map,
					t_map_reader_buffer *tmap_reader_buffer);
void			get_max_cordinates_loop_condition(
					t_map_reader_buffer *curr_reader_buffer, int *nb_detected,
					int *nb_of_dots, int i);
int				get_faded_color(int color, double modifier);
unsigned int	get_color_from_dot(char *str);
char			**get_splitted_line(t_map_reader_buffer *curr_map_line_read,
					t_map_reader_buffer *tmap_reader_buffer, t_map *map, int y);
int				get_z_coordinate_from_dot(char *str);
void			guarantee_valid_pixel(double *x_pixel, double *y_pixel,
					mlx_image_t *img);
void			initialize_draw_targets(t_draw_targets *tdraw_targets,
					t_fdf *fdf);
void			invert_coordinates(t_draw_targets *tdraw_targets);
void			keyboard_control(void *fdf_ptr);
t_map			load_map(const char *map_name);
void			load_map_lines(t_map_reader_buffer **tmap_reader_buffer,
					int fd);
void			map_creator(t_map *map,
					t_map_reader_buffer *tmap_reader_buffer);
int				hex_str_to_long_long(char *str, long long *nb);
void			xiaolin_horizontal_rendering(mlx_image_t *img,
					t_draw_targets *tdraw_targets);
void			xiaolin_vertical_rendering(mlx_image_t *img,
					t_draw_targets *tdraw_targets);

#endif