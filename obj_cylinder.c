/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:51:29 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/10 13:15:00 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	rt_parse_cylinder(const char **line, void *scene)
{
	t_cylinder	*newcy;

	newcy = malloc(sizeof(t_cylinder));
	newcy->coords = rt_parse_vector(line[1]);
	newcy->o_vect = rt_parse_vector(line[2]);
	newcy->dia = ft_atof(line[3]);
	newcy->hight = ft_atof(line[4]);
	newcy->color = rt_parse_colour(line[5]);
	newcy->next = NULL;
	if (((t_scene *)scene)->cy == NULL)
		((t_scene *)scene)->cy = newcy;
	else
	{
		while (((t_scene *)scene)->cy->next != NULL)
			((t_scene *)scene)->cy = ((t_scene *)scene)->cy->next;
		((t_scene *)scene)->cy->next = newcy;
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
