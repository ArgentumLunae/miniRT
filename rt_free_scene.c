/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_free_scene.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 17:16:30 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/10 13:03:45 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

static void	rt_freeamb(t_ambient *a)
{
	free(a->color);
	free(a);
}

void	rt_free_scene(t_scene *scene)
{
	free(scene->origin);
	free(scene->res);
	rt_freeamb(scene->amb);
	rt_freecam(scene->cam);
	rt_freel(scene->light);
	rt_freecy(scene->cy);
	rt_freepl(scene->pl);
	rt_freesp(scene->sp);
	rt_freesq(scene->sq);
	rt_freetr(scene->tr);
	free(scene);
}
