/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 18:57:28 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/29 16:35:27 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_add_shade(double phi, int color, t_ambient *amb, t_light *light)
{
	int		r;
	int		g;
	int		b;
	double	temp;
	double	ramb;

	ramb = 1 - amb->ratio;
	temp = ramb * ((double)light->color->b / 255) * phi * (color % 256);
	b = temp + amb->ratio * (amb->color->b / 255) * (color % 256);
	temp = ramb * ((double)light->color->g / 255) * phi * ((color >> 8) % 256);
	g = temp + amb->ratio * (amb->color->g / 255) * ((color >> 8) % 256);
	temp = ramb * ((double)light->color->r / 255) * phi * ((color >> 16) % 256);
	r = temp + amb->ratio * (amb->color->r / 255) * ((color >> 16) % 256);
	return ((r << 16) + (g << 8) + b);
}