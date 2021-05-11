/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_light.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:49:17 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/29 18:42:16 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	rt_parse_light(const char **line, t_scene *scene)
{
	t_light	*temp;
	t_light	*newlight;

	newlight = malloc(sizeof(t_light));
	newlight->coords = rt_parse_vector(line[1], 1);
	newlight->lux = ft_atof(line[2]);
	newlight->color = rt_parse_colour(line[3]);
	newlight->next = NULL;
	if (scene->light == NULL)
		scene->light = newlight;
	else
	{
		temp = scene->light;
		while (scene->light->next != NULL)
			scene->light = scene->light->next;
		scene->light->next = newlight;
		scene->light = temp;
	}
}

void	rt_freel(t_light *l)
{
	t_light	*temp;

	while (l != NULL)
	{
		temp = l->next;
		free(l->coords);
		free(l->color);
		free(l);
		l = temp;
	}
}
