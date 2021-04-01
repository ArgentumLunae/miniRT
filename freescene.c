/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   freescene.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 15:16:00 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/01 11:48:38 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

static void	rt_freecy(t_cylinder *cy)
{
	t_cylinder	*temp;

	while (cy != NULL)
	{
		temp = cy->next;
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
		free(tr);
		tr = temp;
	}
}

void rt_free_scene(t_scene *scene)
{
	free(scene->resolution);
	free(scene->ambient);
	rt_freecy(scene->cylinder);
	rt_freepl(scene->plane);
	rt_freesp(scene->sphere);
	rt_freesq(scene->square);
	rt_freetr(scene->triangle);
	free(scene);
}
