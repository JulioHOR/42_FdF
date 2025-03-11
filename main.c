/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:37:10 by juhenriq          #+#    #+#             */
/*   Updated: 2025/03/10 22:34:24 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_background(t_fdf *fdf)
{
	int	i;
	int	j;

	j = 0;
	while (j < fdf->y_window_size)
	{
		i = 0;
		while (i < fdf->x_window_size)
			mlx_put_pixel(fdf->img, i++, j, 0x000000FF);
		j++;
	}
}

static void	set_initial_values(t_fdf *fdf, t_map *map)
{
	fdf->map = map;
	fdf->x_window_size = 1920;
	fdf->y_window_size = 1080;
	fdf->x_center = fdf->x_window_size / 2 - 0;
	fdf->y_center = fdf->y_window_size / 2 - 600;
	fdf->zoom_level = 25;
	fdf->scale_factor = 0.1;
	fdf->mlx = mlx_init(fdf->x_window_size, fdf->y_window_size, "FdF", true);
	if (!(fdf->mlx))
	{
		free_map(map);
		exit(1);
	}
	mlx_set_setting(MLX_MAXIMIZED, true);
	fdf->img = mlx_new_image(fdf->mlx, fdf->x_window_size, fdf->y_window_size);
	if (!(fdf->img) || (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) < 0))
	{
		free_map(map);
		mlx_terminate(fdf->mlx);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_fdf	fdf;

	if (argc < 2 || argc > 2)
	{
		ft_printf("An incorrect number of arguments was passed. Please, only "
			"input the map file name and nothing else.");
		exit(1);
	}
	map = load_map(argv[1]);
	set_initial_values(&fdf, &map);
	draw_points(&fdf);
	mlx_loop_hook(fdf.mlx, keyboard_control, &fdf);
	mlx_loop(fdf.mlx);
	free_map(&map);
	mlx_terminate(fdf.mlx);
	return (0);
}
