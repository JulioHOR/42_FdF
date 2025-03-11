/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:46:00 by juhenriq          #+#    #+#             */
/*   Updated: 2025/03/10 22:08:08 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	wa(t_fdf *fdf, int *redraw, int step)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
	{
		fdf->y_center -= step;
		fdf->x_center -= step;
		*redraw = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
	{
		fdf->y_center += step;
		fdf->x_center -= step;
		*redraw = 1;
	}
}

static void	wasd(void *fdf_ptr)
{
	t_fdf	*fdf;
	int		redraw;
	int		step;

	fdf = (t_fdf *) fdf_ptr;
	step = 3;
	redraw = 0;
	wa(fdf, &redraw, step);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
	{
		fdf->x_center += step;
		fdf->y_center += step;
		redraw = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
	{
		fdf->x_center += step;
		fdf->y_center -= step;
		redraw = 1;
	}
	if (redraw)
		draw_points(fdf_ptr);
}

static void	zoom(void *fdf_ptr)
{
	t_fdf	*fdf;
	int		redraw;
	int		step;

	fdf = (t_fdf *) fdf_ptr;
	step = 3;
	redraw = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
	{
		fdf->zoom_level += step;
		redraw = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
	{
		fdf->zoom_level -= step;
		if (fdf->zoom_level < 1)
			fdf->zoom_level = 1;
		redraw = 1;
	}
	if (redraw)
		draw_points(fdf_ptr);
}

static void	scale_factor(void *fdf_ptr)
{
	t_fdf		*fdf;
	int			redraw;
	double		step;

	fdf = (t_fdf *) fdf_ptr;
	step = 0.1;
	redraw = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_ADD))
	{
		fdf->scale_factor += step;
		redraw = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_SUBTRACT))
	{
		fdf->scale_factor -= step;
		redraw = 1;
	}
	if (redraw)
		draw_points(fdf_ptr);
}

void	keyboard_control(void *fdf_ptr)
{
	t_fdf		*fdf;

	fdf = fdf_ptr;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
	{
		free_map(fdf->map);
		mlx_terminate(fdf->mlx);
		exit(0);
	}
	wasd(fdf);
	zoom(fdf);
	scale_factor(fdf);
}
