/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectormaths.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 11:38:04 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/29 17:35:12 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double	rt_vect_dot(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector	*rt_vect_cross(t_vector *v1, t_vector *v2)
{
	t_vector	*cross;

	cross = malloc(sizeof(t_vector));
	cross->x = v1->y * v2->z - v1->z * v2->y;
	cross->y = v1->z * v2->x - v1->x * v2->z;
	cross->z = v1->x * v2->y - v1->y * v2->x;
	return (cross);
}

t_vector	*rt_vect_sub(t_vector *v1, t_vector *v2)
{
	t_vector	*vsub;

	vsub = malloc(sizeof(t_vector));
	vsub->x = v1->x - v2->x;
	vsub->y = v1->y - v2->y;
	vsub->z = v1->z - v2->z;
	return (vsub);
}

t_vector	*rt_vect_add(t_vector *v1, t_vector *v2)
{
	t_vector	*res;

	res = malloc(sizeof(t_vector));	
	res->x = v1->x + v2->x;
	res->y = v1->y + v2->y;
	res->z = v1->z + v2->z;
	return (res);
}

double	rt_vect_mag(t_vector *v1, t_vector *v2)
{
	t_vector	*t;

	t = NULL;
	t = rt_vect_sub(v1, v2);
	return (sqrt((t->x * t->x) + (t->y * t->y) + (t->z * t->z)));
}

/* calculate the angle between vectors using the *
 * directional component of those vectors        */
double	rt_vect_angle(t_vector *v1, t_vector *v2, t_scene *scene)
{
	double		dot;
	double		mag1;
	double		mag2;

	dot = rt_vect_dot(v1, v2);
	mag1 = rt_vect_mag(scene->origin, v1);
	mag2 = rt_vect_mag(scene->origin, v2);
	return (acos(dot / (mag1 * mag2)));
}

t_vector	*rt_vect_scale(double c, t_vector v)
{
	t_vector	*ret;

	ret = malloc(sizeof(t_vector));
	ret->x = c * v.x;
	ret->y = c * v.y;
	ret->z = c * v.z;
	return (ret);
}

t_vector	*rt_vect_dir(t_vector *vs, t_vector *vp)
{
	t_vector	*dir;
	t_vector	*temp;
	double		mag;

	temp = NULL;
	mag = rt_vect_mag(vs, vp);
	temp = rt_vect_sub(vp, vs);
	dir = rt_vect_scale(mag, *temp);
	return (dir);
}

t_vector	*vect_normalize(t_vector *vs, t_vector *vp)
{
	t_vector	*unitvect;
	double		unitscale;

	unitscale = 1 / rt_vect_mag(vs, vp);
	unitvect = rt_vect_scale(unitscale, *rt_vect_sub(vp, vs));
	return (unitvect);
}