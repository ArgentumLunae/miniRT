/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_plane.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:52:38 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/29 18:42:26 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include "vmaths.h"
#include <stdlib.h>

void	rt_parse_plane(const char **line, t_scene *scene)
{
	t_plane	*newpl;
	double	normalize;

	newpl = malloc(sizeof(t_plane));
	newpl->coords = rt_parse_vector(line[1], 1);
	newpl->o_vect = rt_parse_vector(line[2], 0);
	normalize = 1 / rt_vect_mag(scene->origin, newpl->o_vect);
	newpl->o_vect = rt_vect_scale(normalize, *newpl->o_vect);
	newpl->color = rt_parse_colour(line[3]);
	newpl->next = NULL;
	if (scene->pl == NULL)
		scene->pl = newpl;
	else
	{
		while (scene->pl->next != NULL)
			scene->pl = scene->pl->next;
		scene->pl->next = newpl;
	}
}

void	rt_freepl(t_plane *pl)
{
	t_plane	*temp;

	while (pl != NULL)
	{
		temp = pl->next;
		free(pl->coords);
		free(pl->o_vect);
		free(pl->color);
		free(pl);
		pl = temp;
	}
}
