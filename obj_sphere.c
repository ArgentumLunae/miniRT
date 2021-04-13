/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_sphere.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:42:03 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/10 13:06:18 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include <stdlib.h>

/* Add a new sphere object to the list of spheres in the scene.*/
void	rt_parse_sphere(const char **line, void *scene)
{
	t_sphere	*newsp;
	t_sphere	*temp;

	newsp = malloc(sizeof(t_sphere));
	newsp->coords = rt_parse_vector(line[1]);
	newsp->rad = ft_atof(line[2]) / 2;
	newsp->color = rt_parse_colour(line[3]);
	newsp->next = NULL;
	if (((t_scene *)scene)->sp == NULL)
		((t_scene *)scene)->sp = newsp;
	else
	{
		temp = ((t_scene *)scene)->sp;
		while (((t_scene *)scene)->sp->next != NULL)
			((t_scene *)scene)->sp = ((t_scene *)scene)->sp->next;
		((t_scene *)scene)->sp->next = newsp;
		((t_scene *)scene)->sp = temp;
	}
}

void	rt_freesp(t_sphere *sp)
{
	t_sphere	*temp;

	while (sp != 0)
	{
		temp = sp->next;
		free(sp->coords);
		free(sp->color);
		free(sp);
		sp = temp;
	}
}
