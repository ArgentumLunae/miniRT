/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_camera.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:47:02 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/10 14:46:02 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	rt_parse_camera(const char **line, void *scene)
{
	t_camera	*newcam;
	t_camera	*temp;

	newcam = malloc(sizeof(t_camera));
	newcam->coords = rt_parse_vector(line[1]);
	newcam->o_vect = rt_parse_vector(line[2]);
	newcam->fov = ft_atoi(line[3]);
	newcam->next = NULL;
	if (((t_scene *)scene)->cam == NULL)
		((t_scene *)scene)->cam = newcam;
	else
	{
		temp = ((t_scene *)scene)->cam;
		while (((t_scene *)scene)->cam->next != NULL)
			((t_scene *)scene)->cam = ((t_scene *)scene)->cam->next;
		((t_scene *)scene)->cam->next = newcam;
		((t_scene *)scene)->cam = temp;
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
