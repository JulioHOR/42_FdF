/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendering_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:35:38 by juhenriq          #+#    #+#             */
/*   Updated: 2025/03/10 23:05:39 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_draw_targets	*apply_isometry(t_draw_targets *tdraw_targets, int z0,
	int z1,	t_fdf *fdf)
{
	int						temp_x;
	int						temp_y;
	static t_draw_targets	tdraw_targets_isometric;

	tdraw_targets_isometric = *tdraw_targets;
	temp_x = tdraw_targets_isometric.x0;
	temp_y = tdraw_targets_isometric.y0;
	tdraw_targets_isometric.x0 = (temp_x - temp_y) * cos(0.523599);
	tdraw_targets_isometric.y0 = (temp_x + temp_y) * sin(0.523599)
		- (z0 * (fdf->zoom_level * fdf->scale_factor));
	temp_x = tdraw_targets_isometric.x1;
	temp_y = tdraw_targets_isometric.y1;
	tdraw_targets_isometric.x1 = (temp_x - temp_y) * cos(0.523599);
	tdraw_targets_isometric.y1 = (temp_x + temp_y) * sin(0.523599)
		- ((z1 * (fdf->zoom_level * fdf->scale_factor)));
	return (&tdraw_targets_isometric);
}

static void	draw_x_line(t_draw_targets *tdraw_targets, t_fdf *fdf, int y, int x)
{
	int	line_width;

	line_width = fdf->zoom_level;
	tdraw_targets->x1 = tdraw_targets->x0 + line_width;
	draw_line(fdf->img, apply_isometry(tdraw_targets,
			fdf->map->dots[y][x].z_coordinate,
			fdf->map->dots[y][x + 1].z_coordinate,
			fdf));
	tdraw_targets->x0 = tdraw_targets->x1;
}

static void	draw_y_line(t_draw_targets *tdraw_targets, t_fdf *fdf, int y, int x)
{
	int	line_width;

	line_width = fdf->zoom_level;
	tdraw_targets->y1 += line_width;
	draw_line(fdf->img, apply_isometry(tdraw_targets,
			fdf->map->dots[y][x].z_coordinate,
			fdf->map->dots[y + 1][x].z_coordinate,
			fdf));
}

void	draw_points(void *fdf_ptr)
{
	t_draw_targets	tdraw_targets;
	t_draw_targets	copied_tdraw_targets;
	int				x;
	int				y;

	draw_background(((t_fdf *) fdf_ptr));
	initialize_draw_targets(&tdraw_targets, ((t_fdf *) fdf_ptr));
	y = -1;
	while (++y <= ((t_fdf *) fdf_ptr)->map->max_y_coordinate_recorded)
	{
		x = -1;
		while (++x <= ((t_fdf *) fdf_ptr)->map->max_x_coordinate_recorded)
		{
			copied_tdraw_targets = tdraw_targets;
			if (x + 1 <= ((t_fdf *) fdf_ptr)->map->max_x_coordinate_recorded)
				draw_x_line(&tdraw_targets, ((t_fdf *) fdf_ptr), y, x);
			if (y + 1 <= ((t_fdf *) fdf_ptr)->map->max_y_coordinate_recorded)
				draw_y_line(&copied_tdraw_targets, ((t_fdf *) fdf_ptr), y, x);
		}
		tdraw_targets.x0 = ((t_fdf *) fdf_ptr)->x_center;
		tdraw_targets.x1 = ((t_fdf *) fdf_ptr)->x_center;
		tdraw_targets.y0 += ((t_fdf *) fdf_ptr)->zoom_level;
		tdraw_targets.y1 += ((t_fdf *) fdf_ptr)->zoom_level;
	}
}
