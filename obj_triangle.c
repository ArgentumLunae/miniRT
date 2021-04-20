/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_triangle.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:54:07 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/15 13:33:31 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include "vmaths.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void	rt_parse_triangle(const char **line, void *scene)
{
	t_triangle	*newtr;
	double		normalize;

	newtr = malloc(sizeof(t_triangle));
	if (!newtr)
		return ;
	newtr->coord1 = rt_parse_vector(line[1]);
	newtr->coord2 = rt_parse_vector(line[2]);
	newtr->coord3 = rt_parse_vector(line[3]);
	newtr->vone = rt_vect_sub(newtr->coord2, newtr->coord1);
	newtr->vtwo = rt_vect_sub(newtr->coord3, newtr->coord1);
	newtr->vthree = rt_vect_sub(newtr->coord3, newtr->coord2);
	newtr->norm = rt_vect_cross(newtr->vone, newtr->vtwo);
	printf("norm z: %lf\n", newtr->norm->z);
	normalize = 1 / rt_vect_mag(((t_scene *)scene)->origin, newtr->norm);
	newtr->norm = rt_vect_scale(normalize, *newtr->norm);
	newtr->color = rt_parse_colour(line[4]);
	newtr->next = NULL;
	if (((t_scene *)scene)->tr == NULL)
		((t_scene *)scene)->tr = newtr;
	else
	{
		while (((t_scene *)scene)->tr->next != NULL)
			((t_scene *)scene)->tr = ((t_scene *)scene)->tr->next;
		((t_scene *)scene)->tr->next = newtr;
	}
}

bool	rt_tr_intersect(t_camera *cam, t_triangle *tr, double *t)
{
	double		dist;
	double		denom;
	double		tt;
	t_vector	*q;
	t_vector	*cross;

	dist = rt_vect_dot(tr->norm, tr->coord1);
	denom = rt_vect_dot(tr->norm, &cam->rdir);
	if (denom == 0)
		return (false);
	tt = (dist - rt_vect_dot(tr->norm, cam->coords)) / denom;
	if (tt < *t)
	{
		q = rt_vect_scale(tt, cam->rdir);
		cross = rt_vect_cross(tr->vone, rt_vect_sub(q, tr->coord1));
		if (rt_vect_dot(cross, tr->norm) >= 0)
		{
			free(cross);
			cross = rt_vect_cross(rt_vect_sub(q, tr->coord1), tr->vtwo);
			if (rt_vect_dot(cross, tr->norm) >= 0)
			{
				free(cross);
				cross = rt_vect_cross(tr->vthree, rt_vect_sub(q, tr->coord2));
				if (rt_vect_dot(cross, tr->norm) >= 0)
				{
					*t = tt;
					if (cam->rdir.x == 0 && cam->rdir.y == 0)
						printf("normal: %lf,%lf,%lf\ndist: %lf\ndenom: %lf\ntt: %lf\nq: %lf,%lf,%lf\n", tr->norm->x, tr->norm->y, tr->norm->z, dist, denom, tt, q->x, q->y, q->z);
					free(q);
					free(cross);
					return (true);
				}
			}
		}
		free(q);
		free(cross);
	}
	return (false);
}

void	rt_freetr(t_triangle *tr)
{
	t_triangle	*temp;

	while (tr != NULL)
	{
		temp = tr->next;
		free(tr->coord1);
		free(tr->coord2);
		free(tr->coord3);
		free(tr->vone);
		free(tr->vtwo);
		free(tr->norm);
		free(tr->color);
		free(tr);
		tr = temp;
	}
}
