/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_light_angle.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 18:29:50 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/20 15:12:47 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rtscene.h"
#include "vmaths.h"
#include <math.h>
#include <stdlib.h>

double	rt_light_sp(t_scene *scene, t_sphere *fsp)
{
	t_vector	*norm;
	t_vector	*ldir;
	double		magl;
	double		magn;
	double		phi;

	norm = rt_vect_sub(&scene->cam->rdir, fsp->coords);
	norm = rt_vect_scale(1 / rt_vect_mag(scene->origin, norm), *norm);
	ldir = scene->light->rdir;
	ldir = rt_vect_scale(1 / rt_vect_mag(scene->origin, ldir), *ldir);
	magl = rt_vect_mag(scene->origin, ldir);
	magn = rt_vect_mag(scene->origin, norm);
	phi = acos(rt_vect_dot(ldir, norm) / (magl * magn));
	free(norm);
	if (phi < M_PI_2)
		return (0);
	return (fabs((phi - M_PI_2) / M_PI_2));
}

double	rt_light_pl(t_scene *scene, t_plane *fpl)
{
	t_vector	*ldir;
	double		magl;
	double		magn;
	double		phi;

	ldir = scene->light->rdir;
	ldir = rt_vect_scale(1 / rt_vect_mag(scene->origin, ldir), *ldir);
	magl = rt_vect_mag(scene->origin, ldir);
	magn = rt_vect_mag(scene->origin, fpl->o_vect);
	phi = acos(rt_vect_dot(ldir, fpl->o_vect) / (magl * magn));
	return (fabs((phi - M_PI_2) / M_PI_2));
}

double	rt_light_tr(t_scene *scene, t_triangle *ftr)
{
	t_vector	*ldir;
	double		magl;
	double		magn;
	double		phi;

	ldir = scene->light->rdir;
	ldir = rt_vect_scale(1 / rt_vect_mag(scene->origin, ldir), *ldir);
	magl = rt_vect_mag(scene->origin, ldir);
	magn = rt_vect_mag(scene->origin, ftr->norm);
	phi = acos(rt_vect_dot(ldir, ftr->norm) / (magl * magn));
	return (fabs((phi - M_PI_2) / M_PI_2));
}

double	rt_light_sq(t_scene *scene, t_square *fsq)
{
	t_vector	*ldir;
	double		magl;
	double		magn;
	double		phi;

	ldir = scene->light->rdir;
	ldir = rt_vect_scale(1 / rt_vect_mag(scene->origin, ldir), *ldir);
	magl = rt_vect_mag(scene->origin, ldir);
	magn = rt_vect_mag(scene->origin, fsq->o_vect);
	phi = acos(rt_vect_dot(ldir, fsq->o_vect) / (magl * magn));
	return (fabs((phi - M_PI_2) / M_PI_2));
}
