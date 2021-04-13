/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_plane.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:52:38 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/10 13:08:26 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	rt_parse_plane(const char **line, void *scene)
{
	t_plane	*newpl;

	newpl = malloc(sizeof(t_plane));
	newpl->coords = rt_parse_vector(line[1]);
	newpl->o_vect = rt_parse_vector(line[2]);
	newpl->color = rt_parse_colour(line[3]);
	newpl->next = NULL;
	if (((t_scene *)scene)->pl == NULL)
		((t_scene *)scene)->pl = newpl;
	else
	{
		while (((t_scene *)scene)->pl->next != NULL)
			((t_scene *)scene)->pl = ((t_scene *)scene)->pl->next;
		((t_scene *)scene)->pl->next = newpl;
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
