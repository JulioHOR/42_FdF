/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_rendering_vertical.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:29:41 by juhenriq          #+#    #+#             */
/*   Updated: 2025/03/10 22:18:28 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	xiaolin_vertical_rendering_first_pixel(mlx_image_t *img,
	t_draw_targets *tdraw_targets)
{
	double	x_pixel;
	double	y_pixel;
	double	overlap;
	double	dist_start;

	overlap = 1 - ((tdraw_targets->y0 + 0.5))
		- ((int)(tdraw_targets->y0 + 0.5));
	dist_start = tdraw_targets->y0 - ((int) tdraw_targets->y0);
	x_pixel = (int) tdraw_targets->x0 + 0.5;
	y_pixel = (int) tdraw_targets->y0;
	guarantee_valid_pixel(&x_pixel, &y_pixel, img);
	mlx_put_pixel(img, x_pixel, y_pixel,
		get_faded_color(WHITE, ((1 - dist_start) * overlap)));
	y_pixel = ((int) tdraw_targets->y0) + 1;
	guarantee_valid_pixel(&x_pixel, &y_pixel, img);
	mlx_put_pixel(img, x_pixel, y_pixel,
		get_faded_color(WHITE, dist_start * overlap));
}

static void	xiaolin_vertical_rendering_first_and_last_pixels(mlx_image_t *img,
	t_draw_targets *tdraw_targets)
{
	double	x_pixel;
	double	y_pixel;
	double	overlap;
	double	dist_end;

	if (first_and_last_pixels_validator(tdraw_targets, img))
		return ;
	xiaolin_vertical_rendering_first_pixel(img, tdraw_targets);
	overlap = ((tdraw_targets->y1 - 0.5)) - ((int)(tdraw_targets->y1 - 0.5));
	dist_end = tdraw_targets->y1 - ((int) tdraw_targets->y1);
	x_pixel = (int) tdraw_targets->x1;
	y_pixel = (int) tdraw_targets->y1 + 0.5;
	guarantee_valid_pixel(&x_pixel, &y_pixel, img);
	mlx_put_pixel(img, x_pixel, y_pixel,
		get_faded_color(WHITE, ((1 - dist_end) * overlap)));
	x_pixel = ((int) tdraw_targets->x1) + 1;
	guarantee_valid_pixel(&x_pixel, &y_pixel, img);
	mlx_put_pixel(img, x_pixel,
		y_pixel,
		get_faded_color(WHITE, dist_end * overlap));
}

static void	xiaolin_vertical_put_pixel_loop(double delta_y,
	t_draw_targets *tdraw_targets, mlx_image_t *img, double m)
{
	double	x_pixel;
	double	y_pixel;
	double	pixel_delta;
	int		i;

	i = 0;
	while (++i <= ((int) round(delta_y + 0.5)))
	{
		x_pixel = tdraw_targets->x0 + (i * m);
		y_pixel = tdraw_targets->y0 + i;
		pixel_delta = y_pixel - (int) y_pixel;
		if (((x_pixel >= img->width || x_pixel < 0)
				|| (y_pixel >= img->height || y_pixel < 0))
			|| (((int) floor(x_pixel)) + 1 >= (int) img->width))
			continue ;
		guarantee_valid_pixel(&x_pixel, &y_pixel, img);
		mlx_put_pixel(img, (int) floor(x_pixel), ((int) floor(y_pixel)),
			get_faded_color(tdraw_targets->color_0, pixel_delta));
		mlx_put_pixel(img, (int) floor(x_pixel) + 1, (int) floor(y_pixel),
			tdraw_targets->color_0);
	}
}

void	xiaolin_vertical_rendering(mlx_image_t *img,
	t_draw_targets *tdraw_targets)
{
	double	delta_x;
	double	delta_y;
	double	m;

	if (tdraw_targets->y1 < tdraw_targets->y0)
		invert_coordinates(tdraw_targets);
	delta_x = tdraw_targets->x1 - tdraw_targets->x0;
	delta_y = tdraw_targets->y1 - tdraw_targets->y0;
	if (delta_y != 0)
		m = delta_x / delta_y;
	else
		m = 1;
	xiaolin_vertical_rendering_first_and_last_pixels(img, tdraw_targets);
	xiaolin_vertical_put_pixel_loop(delta_y, tdraw_targets, img, m);
}
