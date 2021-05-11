/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_sphere_inter.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 17:06:07 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/05/11 16:36:48 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <math.h>
#include "minirt.h"
#include "vmaths.h"
#include <stdio.h>

static bool	closest_inter(t_discriminant *disc, double *t)
{
	double	sqrtd;
	double	tzero;
	double	tone;

	sqrtd = sqrt(disc->d);
	tzero = (-disc->b + sqrtd) / (2 * disc->a);
	tone = (-disc->b - sqrtd) / (2 * disc->a);
	if (tzero > tone)
		tzero = tone;
	
	if (tzero > 0.0000001 && tzero < *t)
	{
		*t = tzero;
		//printf("t = %lf\n", *t);
		return (true);
	}
	return (false);
}

bool	rt_sphere_inter(t_camera *c, t_sphere *s, double *t)
{
	t_discriminant	disc;
	t_vector		*dist;

	disc.a = rt_vect_dot(&c->rdir, &c->rdir);
	dist = rt_vect_sub(c->coords, s->coords);
	disc.b = 2 * rt_vect_dot(&c->rdir, dist);
	disc.c = rt_vect_dot(dist, dist) - (s->rad * s->rad);
	disc.d = disc.b * disc.b - 4 * disc.a * disc.c;
	if (disc.d >= 0)
		return (closest_inter(&disc, t));
	return (false);
}
