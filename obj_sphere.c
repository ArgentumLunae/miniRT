/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_sphere.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:42:03 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/20 10:37:47 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include <stdlib.h>

/* Add a new sphere object to the list of spheres in the scene.*/
void	rt_parse_sphere(const char **line, t_scene *scene)
{
	t_sphere	*newsp;
	t_sphere	*temp;

	newsp = malloc(sizeof(t_sphere));
	newsp->coords = rt_parse_vector(line[1]);
	newsp->rad = ft_atof(line[2]) / 2;
	newsp->color = rt_parse_colour(line[3]);
	newsp->next = NULL;
	if (scene->sp == NULL)
		scene->sp = newsp;
	else
	{
		temp = scene->sp;
		while (scene->sp->next != NULL)
			scene->sp = scene->sp->next;
		scene->sp->next = newsp;
		scene->sp = temp;
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
