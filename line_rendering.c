/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 01:52:08 by juhenriq          #+#    #+#             */
/*   Updated: 2025/03/10 22:33:40 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	invert_coordinates(t_draw_targets *tdraw_targets)
{
	int		temp_x;
	int		temp_y;

	temp_x = tdraw_targets->x0;
	tdraw_targets->x0 = tdraw_targets->x1;
	tdraw_targets->x1 = temp_x;
	temp_y = tdraw_targets->y0;
	tdraw_targets->y0 = tdraw_targets->y1;
	tdraw_targets->y1 = temp_y;
}

int	first_and_last_pixels_validator(t_draw_targets *tdraw_targets,
	mlx_image_t *img)
{
	if (((tdraw_targets->x0 >= (int) img->width || tdraw_targets->x0 < 0)
			|| (tdraw_targets->x1 >= (int) img->width || tdraw_targets->x1 < 0))
		|| ((tdraw_targets->y0 >= (int) img->height || tdraw_targets->y0 < 0)
			|| (tdraw_targets->y1 >= (int) img->height
				|| tdraw_targets->y1 < 0)))
		return (1);
	return (0);
}

void	draw_line(mlx_image_t *img, t_draw_targets *tdraw_targets)
{
	if (abs(tdraw_targets->y1 - tdraw_targets->y0)
		< abs(tdraw_targets->x1 - tdraw_targets->x0))
		xiaolin_horizontal_rendering(img, tdraw_targets);
	else
		xiaolin_vertical_rendering(img, tdraw_targets);
}

void	initialize_draw_targets(t_draw_targets *tdraw_targets, t_fdf *fdf)
{
	tdraw_targets->x0 = fdf->x_center;
	tdraw_targets->x1 = fdf->x_center;
	tdraw_targets->y0 = fdf->y_center;
	tdraw_targets->y1 = fdf->y_center;
	tdraw_targets->color_0 = 0xFFFFFFFF;
	tdraw_targets->color_1 = 0xFFFFFFFF;
}
