/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_camera.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:47:02 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/29 18:42:06 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	rt_parse_camera(const char **line, t_scene *scene)
{
	t_camera	*newcam;
	t_camera	*temp;

	newcam = malloc(sizeof(t_camera));
	newcam->coords = rt_parse_vector(line[1], 1);
	newcam->o_vect = rt_parse_vector(line[2], 0);
	newcam->fov = ft_atoi(line[3]);
	newcam->next = NULL;
	if (scene->cam == NULL)
		scene->cam = newcam;
	else
	{
		temp = scene->cam;
		while (scene->cam->next != NULL)
			scene->cam = scene->cam->next;
		scene->cam->next = newcam;
		scene->cam = temp;
	}
}

void	rt_freecam(t_camera *c)
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
