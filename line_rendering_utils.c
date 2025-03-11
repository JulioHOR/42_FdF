/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_rendering_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:28:05 by juhenriq          #+#    #+#             */
/*   Updated: 2025/03/10 23:05:27 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	guarantee_valid_pixel(double *x_pixel, double *y_pixel,
	mlx_image_t *img)
{
	if (*x_pixel >= img->width)
		*x_pixel = img->width - 1;
	if (*y_pixel >= img->height)
		*y_pixel = img->height - 1;
	if (*x_pixel < 0)
		*x_pixel = 0;
	if (*y_pixel < 0)
		*y_pixel = 0;
}

int	get_faded_color(int color, double modifier)
{
	int	alpha_channel;
	int	faded_color;

	alpha_channel = (int)(255 * (1 - modifier));
	faded_color = (color & 0xFFFFFF00) | alpha_channel;
	return (faded_color);
}
