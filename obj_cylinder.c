/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:51:29 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/29 18:43:59 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include "vmaths.h"
#include <stdlib.h>
#include <stdbool.h>

void	rt_parse_cylinder(const char **line, t_scene *scene)
{
	t_cylinder	*newcy;
	double		normalize;

	newcy = malloc(sizeof(t_cylinder));
	newcy->coords = rt_parse_vector(line[1], 1);
	newcy->o_vect = rt_parse_vector(line[2], 0);
	normalize = 1 / rt_vect_mag(scene->origin, newcy->o_vect);
	newcy->o_vect = rt_vect_scale(normalize, *newcy->o_vect);
	newcy->dia = ft_atof(line[3]);
	newcy->hight = ft_atof(line[4]);
	newcy->top = rt_vect_add(newcy->coords, rt_vect_scale(newcy->hight / 2, *newcy->o_vect));
	newcy->top = rt_vect_sub(newcy->coords, rt_vect_scale(newcy->hight / 2, *newcy->o_vect));
	newcy->color = rt_parse_colour(line[5]);
	newcy->next = NULL;
	if (scene->cy == NULL)
		scene->cy = newcy;
	else
	{
		while (scene->cy->next != NULL)
			scene->cy = scene->cy->next;
		scene->cy->next = newcy;
	}
}

void	rt_freecy(t_cylinder *cy)
{
	t_cylinder	*temp;

	while (cy != NULL)
	{
		temp = cy->next;
		free(cy->coords);
		free(cy->o_vect);
		free(cy->color);
		free(cy);
		cy = temp;
	}
}
