/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   freescene.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:16:00 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/02 16:28:26 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

static void	rt_freeamb(t_ambient *a)
{
	free(a->colour);
	free(a);
}

static void	rt_freecam(t_camera *c)
{
	t_camera	*temp;

	while (c != NULL)
	{
		temp = c->next;
		free(c->coords);
		free(c->o_vect);
		free(c);
		c = temp;
	}
}

static void rt_freel(t_light *l)
{
	t_light	*temp;

	while (l != NULL)
	{
		temp = l->next;
		free(l->coords);
		free(l->colour);
		free(l);
		l = temp;
	}
}

static void	rt_freecy(t_cylinder *cy)
{
	t_cylinder	*temp;

	while (cy != NULL)
	{
		temp = cy->next;
		free(cy->coords);
		free(cy->colour);
		free(cy);
		cy = temp;
	}
}

static void	rt_freepl(t_plane *pl)
{
	t_plane	*temp;

	while (pl != NULL)
	{
		temp = pl->next;
		free(pl->coords);
		free(pl->o_vect);
		free(pl->colour);
		free(pl);
		pl = temp;
	}
}

static void	rt_freesp(t_sphere *sp)
{
	t_sphere	*temp;

	while (sp != NULL)
	{
		temp = sp->next;
		free(sp->coords);
		free(sp->colour);
		free(sp);
		sp = temp;
	}
}

static void	rt_freesq(t_square *sq)
{
	t_square	*temp;

	while (sq != NULL)
	{
		temp = sq->next;
		free(sq->coords);
		free(sq->o_vect);
		free(sq->colour);
		free(sq);
		sq = temp;
	}
}

static void	rt_freetr(t_triangle *tr)
{
	t_triangle	*temp;

	while (tr != NULL)
	{
		temp = tr->next;
		free(tr->coord1);
		free(tr->coord2);
		free(tr->coord3);
		free(tr->colour);
		free(tr);
		tr = temp;
	}
}

void rt_free_scene(t_scene *scene)
{
	free(scene->resolution);
	rt_freeamb(scene->ambient);
	rt_freecam(scene->camera);
	rt_freel(scene->light);
	rt_freecy(scene->cylinder);
	rt_freepl(scene->plane);
	rt_freesp(scene->sphere);
	rt_freesq(scene->square);
	rt_freetr(scene->triangle);
	free(scene);
}
