/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 18:57:28 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/13 11:14:33 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_add_shade(double distance, int color, t_ambient *amb, t_light *light)
{
	int		r;
	int		g;
	int		b;

	if ((light->color->b / 255) > amb->ratio)
		b = (light->color->b / 255) * distance * (color % 256);
	else
		b = (amb->color->b / 255) * amb->ratio * (color % 256);
	if ((light->color->g / 255) > amb->ratio)
		g = (light->color->g / 255) * distance * ((color >> 8) % 256);
	else
		g = (amb->color->g / 255) * amb->ratio * ((color >> 8) % 256);
	if ((light->color->r / 255) > amb->ratio)
		r = (light->color->r / 255) * distance * ((color >> 16) % 256);
	else
		r = (amb->color->r / 255) * amb->ratio * ((color >> 16) % 256);
	return ((r << 16) + (g << 8) + b);
}