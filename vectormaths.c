/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectormaths.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 11:38:04 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/06 19:53:20 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdlib.h>

double	rt_vector_dot(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector	rt_vector_sub(t_vector *v1, t_vector *v2)
{
	t_vector	vsub;

	vsub.x = v1->x - v2->x;
	vsub.y = v1->y - v2->y;
	vsub.z = v1->z - v2->z;
	return (vsub);
}

t_vector	rt_vector_add(t_vector *v1, t_vector *v2)
{
	t_vector	res;

	res.x = v1->x + v2->x;
	res.y = v1->y + v2->y;
	res.z = v1->z + v2->z;
	return (res);
}

double	rt_vector_mag(t_vector *v1, t_vector *v2)
{
	t_vector	t;

	t = rt_vector_sub(v1, v2);
	return (sqrt((t.x * t.x) + (t.y * t.y) + (t.z * t.z)));
}

/* calculate the angle between vectors using the directional component of those vectors */
double	rt_vector_angle(t_vector *v1, t_vector *v2)
{
	double		dot;
	double		mag1;
	double		mag2;
	t_vector	origin;

	origin = rt_vector_sub(v1, v1);
	dot = rt_vector_dot(v1, v2);
	mag1 = rt_vector_mag(&origin, v1);
	mag2 = rt_vector_mag(&origin, v2);
	return (acos(dot / (mag1 * mag2)));
}

t_vector	*rt_vector_scale(double c, t_vector v)
{
	t_vector	*ret;

	ret = malloc(sizeof(t_vector));
	ret->x = c * v.x;
	ret->y = c * v.y;
	ret->z = c * v.z;
	return (ret);
}

t_vector	*rt_vector_dir(t_vector *vs, t_vector *vp)
{
	t_vector	*dir;
	t_vector	temp;
	double		mag;

	mag = rt_vector_mag(vs, vp);
	temp = rt_vector_sub(vp, vs);
	dir = rt_vector_scale(mag, temp);
	return (dir);
}
