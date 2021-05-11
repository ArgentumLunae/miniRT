/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_square.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:53:29 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/29 18:57:38 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include "vmaths.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

void	rt_base_square(t_scene *scene)
{
	t_square	*base;
	t_vector	*temp;
	t_vector	*i;
	t_vector	*j;

	base = malloc(sizeof(t_square));
	if (!base)
		return ;
	base->coords = scene->origin;
	base->o_vect = rt_parse_vector("0,0,1", 0);
	i = rt_parse_vector("1,0,0", 0);
	j = rt_parse_vector("0,1,0", 0);
	base->c1 = rt_vect_add(i, j);
	base->c2 = rt_vect_sub(i, j);
	base->c3 = rt_vect_sub(j, i);
	temp = rt_vect_scale(-1, *i);
	base->c4 = rt_vect_sub(temp, j);
	free(temp);
}

void	rt_parse_square(const char **line, t_scene *scene)
{
	t_square	*newsq;
	t_square	*tempsq;
	t_vector	*tempv;

	newsq = malloc(sizeof(t_square));
	newsq->coords = rt_parse_vector(line[1], 1);
	tempv = rt_parse_vector(line[2], 0);
	newsq->o_vect = vect_normalize(scene->origin, tempv);
	free(tempv);
	printf("square coordinates:\n\t%lf,%lf,%lf\n\n", newsq->coords->x, newsq->coords->y, newsq->coords->z);
	printf("orientation vector:\n\t%lf,%lf,%lf\n\n", newsq->o_vect->x, newsq->o_vect->y, newsq->o_vect->z);
	if (scene->sq == NULL)
		scene->sq = newsq;
	else
	{
		tempsq = scene->sq;
		while (scene->sq->next != NULL)
			scene->sq = scene->sq->next;
		scene->sq->next = newsq;
		scene->sq = tempsq;
	}
}

bool	rt_sq_intersect(t_camera *cam, t_square *sq, t_scene *sc, double *t)
{
	double		dist;
	double		denom;
	double		tt;
	t_vector	*x;
	t_vector	*y;
	t_vector	*c1;
	t_vector	*c2;
	t_vector	*p;
	t_vector	*q;

	dist = rt_vect_dot(sq->o_vect, sq->coords);
	denom = rt_vect_dot(sq->o_vect, &cam->rdir);
	if (denom == 0)
		return (false);
	tt = (dist - rt_vect_dot(sq->o_vect, cam->coords)) / denom;
	if (tt < *t)
	{
		y = rt_parse_vector("1.0,0.0,0.0", 0);
		if (fabs(rt_vect_dot(y, sq->o_vect)/rt_vect_mag(sc->origin, sq->o_vect)) > 0.75)
			y = rt_parse_vector("0.0,1.0,0.0", 0);
		x = rt_vect_cross(y, sq->o_vect);
		y = rt_vect_cross(sq->o_vect, x);
		x = rt_vect_scale(sq->side_size / 2, *rt_vect_scale(1 / rt_vect_mag(sc->origin, x), *x));
		y = rt_vect_scale(sq->side_size / 2, *rt_vect_scale(1 / rt_vect_mag(sc->origin, y), *y));
		c1 = rt_vect_add(rt_vect_add(sq->coords, x), y);
		c2 = rt_vect_sub(rt_vect_sub(sq->coords, x), y);
		p = rt_vect_scale(tt, cam->rdir);
		q = rt_vect_sub(p, c1);
		if (fabs(rt_vect_angle(rt_vect_sub(sq->coords, c1), q, sc)) <= M_PI_4)
		{
			q = rt_vect_sub(p, c2);
			if (fabs(rt_vect_angle(rt_vect_sub(sq->coords, c2), q, sc)) <= M_PI_4)
			{
				*t = tt;
				free(x);
				free(y);
				free(c1);
				free(c2);
				free(q);
				return (true);
			}
		}
	}
	return (false);
}

void	rt_freesq(t_square *sq)
{
	t_square	*temp;

	while (sq != NULL)
	{
		temp = sq->next;
		free(sq->coords);
		free(sq->o_vect);
		free(sq->color);
		free(sq);
		sq = temp;
	}
}
