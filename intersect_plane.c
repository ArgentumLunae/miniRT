/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_plane.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/12 14:34:20 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/12 16:39:20 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vmaths.h"
#include <math.h>
#include <stdio.h>

bool	rt_plane_inter(t_camera *cam, t_plane *pl, double *t)
{
	double	dist;
	double	c;
	double	p;
	double	d;

	d = rt_vect_dot(pl->o_vect, &cam->rdir);
	if (d == 0)
		return (false);
	p = rt_vect_dot(pl->o_vect, cam->coords);
	c = rt_vect_dot(pl->o_vect, pl->coords);
	dist = fabs((p - c) / d);
	if (dist > 0.0001f && dist < *t)
	{
		*t = dist;
		return (true);
	}
	return (false);
}
