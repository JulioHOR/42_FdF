/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_rendering_horizontal.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:32:43 by juhenriq          #+#    #+#             */
/*   Updated: 2025/03/10 22:18:28 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	xiaolin_horizontal_rendering_endpoints(mlx_image_t *img,
	int x, int y, double overlap)
{
	double	x_pixel;
	double	y_pixel;
	double	dist_start;

	dist_start = y - ((int) y);
	x_pixel = ((int) x + 0.5);
	y_pixel = (int) y;
	guarantee_valid_pixel(&x_pixel, &y_pixel, img);
	mlx_put_pixel(img, x_pixel, y_pixel,
		get_faded_color(WHITE, ((1 - dist_start) * overlap)));
	y_pixel = ((int) y) + 1;
	guarantee_valid_pixel(&x_pixel, &y_pixel, img);
	mlx_put_pixel(img, x_pixel,
		y_pixel, get_faded_color(WHITE, dist_start * overlap));
}

static void	xiaolin_horizontal_draw_endpoints(mlx_image_t *img,
	t_draw_targets *tdraw_targets)
{
	double	overlap;

	if (first_and_last_pixels_validator(tdraw_targets, img))
		return ;
	overlap = 1 - ((tdraw_targets->x0 + 0.5))
		- ((int)(tdraw_targets->x0 + 0.5));
	xiaolin_horizontal_rendering_endpoints(img,
		tdraw_targets->x0, tdraw_targets->y0, overlap);
	overlap = ((tdraw_targets->x1 - 0.5)) - ((int)(tdraw_targets->x1 - 0.5));
	xiaolin_horizontal_rendering_endpoints(img,
		tdraw_targets->x1, tdraw_targets->y1, overlap);
}

static void	xiaolin_horizontal_put_pixel_loop(double delta_x,
	t_draw_targets *tdraw_targets, mlx_image_t *img, double m)
{
	double	x_pixel;
	double	y_pixel;
	double	pixel_delta;
	int		i;

	i = 0;
	while (++i <= ((int) round(delta_x + 0.5)))
	{
		x_pixel = tdraw_targets->x0 + i;
		y_pixel = tdraw_targets->y0 + (i * m);
		pixel_delta = y_pixel - (int) y_pixel;
		if (((x_pixel >= img->width || x_pixel < 0)
				|| (y_pixel >= img->height || y_pixel < 0))
			|| (((int) floor(y_pixel)) + 1 >= (int) img->height))
			continue ;
		guarantee_valid_pixel(&x_pixel, &y_pixel, img);
		mlx_put_pixel(img, (int) floor(x_pixel), (int) floor(y_pixel),
			tdraw_targets->color_0);
		mlx_put_pixel(img, (int) floor(x_pixel), ((int) y_pixel) + 1,
			get_faded_color(tdraw_targets->color_0, pixel_delta));
	}
}

void	xiaolin_horizontal_rendering(mlx_image_t *img,
	t_draw_targets *tdraw_targets)
{
	double	delta_x;
	double	delta_y;
	double	m;

	if (tdraw_targets->x1 < tdraw_targets->x0)
		invert_coordinates(tdraw_targets);
	delta_x = tdraw_targets->x1 - tdraw_targets->x0;
	delta_y = tdraw_targets->y1 - tdraw_targets->y0;
	if (delta_x != 0)
		m = delta_y / delta_x;
	else
		m = 1;
	xiaolin_horizontal_draw_endpoints(img, tdraw_targets);
	xiaolin_horizontal_put_pixel_loop(delta_x, tdraw_targets, img, m);
}
