/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 18:57:28 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/20 12:12:02 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_add_shade(double distance, int color, t_ambient *amb, t_light *light)
{
	int		r;
	int		g;
	int		b;
	double	ramb;

	ramb = 1 - amb->ratio;
	b = ramb * (light->color->b / 255) * distance * (color % 256);
	b += amb->ratio * (amb->color->b / 255) * (color % 256);
	g = ramb * (light->color->g / 255) * distance * ((color >> 8) % 256);
	g += amb->ratio * (amb->color->g / 255) * ((color >> 8) % 256);
	r = ramb * (light->color->r / 255) * distance * ((color >> 16) % 256);
	r += amb->ratio * (amb->color->r / 255) * ((color >> 16) % 256);
	return ((r << 16) + (g << 8) + b);
}