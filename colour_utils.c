/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 18:57:28 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/10 13:01:02 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt_add_shade(double distance, int color, t_scene *scene)
{
	int		r;
	int		g;
	int		b;

	if ((scene->light->color->b / 255) > scene->amb->ratio)
		b = (scene->light->color->b / 255) * distance * (color % 256);
	else
		b = (scene->amb->color->b / 255) * 0.2 * (color % 256);
	if ((scene->light->color->g / 255) > scene->amb->ratio)
		g = (scene->light->color->g / 255) * distance * ((color >> 8) % 256);
	else
		g = (scene->amb->color->g / 255) * 0.2 * ((color >> 8) % 256);
	if ((scene->light->color->r / 255) > scene->amb->ratio)
		r = (scene->light->color->r / 255) * distance * ((color >> 16) % 256);
	else
		r = (scene->amb->color->r / 255) * 0.2 * ((color >> 16) % 256);
	return ((r << 16) + (g << 8) + b);
}