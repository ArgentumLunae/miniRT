/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   startparce.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 19:16:49 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/02 16:28:59 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include "minirt.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	rt_freesplit(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_vector	*rt_parse_vector(const char *str)
{
	t_vector	*coords;
	char		**split;

	split = ft_split(str, ',');
	coords = malloc(sizeof(t_vector));
	coords->x = ft_atof(split[0]);
	coords->y = ft_atof(split[1]);
	coords->z = ft_atof(split[2]);
	rt_freesplit(split);
	return (coords);
}

t_rgb	*rt_parse_colour(const char *str)
{
	t_rgb	*colour;
	char	**split;

	split = ft_split(str, ',');
	colour = malloc(sizeof(t_rgb));
	colour->r = ft_atoi(split[0]);
	colour->g = ft_atoi(split[1]);
	colour->b = ft_atoi(split[2]);
	rt_freesplit(split);
	return (colour);
}

void	rt_parse_light(const char **line, void *scene)
{
	t_light	*temp;
	t_light	*newlight;

	printf("parce light\n");
	newlight = malloc(sizeof(t_light));
	newlight->coords = rt_parse_vector(line[1]);
	newlight->lux = ft_atof(line[2]);
	newlight->colour = rt_parse_colour(line[3]);
	newlight->next = NULL;
	
	if (((t_scene *)scene)->light == NULL)
		((t_scene *)scene)->light = newlight;
	else
	{
		temp = ((t_scene *)scene)->light;
		while (((t_scene *)scene)->light->next != NULL)
			((t_scene *)scene)->light = ((t_scene *)scene)->light->next;
		((t_scene *)scene)->light->next = newlight;
		((t_scene *)scene)->light = temp;
	}
	
}

void	rt_parse_camera(const char **line, void *scene)
{
	t_camera	*newcamera;
	t_camera	*temp;

	printf("parce camera\n");
	newcamera = malloc(sizeof(t_camera));
	newcamera->coords = rt_parse_vector(line[1]);
	newcamera->o_vect = rt_parse_vector(line[2]);
	newcamera->fov = ft_atoi(line[3]);
	newcamera->next = NULL;
	if (((t_scene *)scene)->camera == NULL)
		((t_scene *)scene)->camera = newcamera;
	else
	{
		temp = ((t_scene *)scene)->camera;
		while (((t_scene *)scene)->camera->next != NULL)
			((t_scene *)scene)->camera = ((t_scene *)scene)->camera->next;
		((t_scene *)scene)->camera->next = newcamera;
		((t_scene *)scene)->camera = temp;
	}
	
}

void	rt_parse_sphere(const char **line, void *scene)
{
	t_sphere	*newsphere;
	t_sphere	*temp;

	newsphere = malloc(sizeof(t_sphere));
	newsphere->coords = rt_parse_vector(line[1]);
	newsphere->rad = ft_atof(line[2]);
	newsphere->colour = rt_parse_colour(line[3]);
	newsphere->next = NULL;
	if (((t_scene *)scene)->sphere == NULL)
		((t_scene *)scene)->sphere = newsphere;
	else
	{
		temp = ((t_scene *)scene)->sphere;
		while (((t_scene *)scene)->sphere->next != NULL)
			((t_scene *)scene)->sphere = ((t_scene *)scene)->sphere->next;
		((t_scene *)scene)->sphere->next = newsphere;
		((t_scene *)scene)->sphere = temp;
	}
}

void	rt_parse_plane(const char **line, void *scene)
{
	t_plane	*newplane;

	newplane = malloc(sizeof(t_plane));
	newplane->coords = rt_parse_vector(line[1]);
	newplane->o_vect = rt_parse_vector(line[2]);
	newplane->colour = rt_parse_colour(line[3]);
	newplane->next = NULL;
	if (((t_scene *)scene)->plane == NULL)
		((t_scene *)scene)->plane = newplane;
	else
	{
		while (((t_scene *)scene)->plane->next != NULL)
			((t_scene *)scene)->plane = ((t_scene *)scene)->plane->next;	
		((t_scene *)scene)->plane->next = newplane;
	}
}

void	rt_parse_cylinder(const char **line, void *scene)
{
	t_cylinder	*newcylinder;

	newcylinder = malloc(sizeof(t_cylinder));
	newcylinder->coords = rt_parse_vector(line[1]);
	newcylinder->o_vect = rt_parse_vector(line[2]);
	newcylinder->dia = ft_atof(line[3]);
	newcylinder->hight = ft_atof(line[4]);
	newcylinder->colour = rt_parse_colour(line[5]);
	newcylinder->next = NULL;
	if (((t_scene *)scene)->cylinder == NULL)
		((t_scene *)scene)->cylinder = newcylinder;
	else
	{
		while (((t_scene *)scene)->cylinder->next != NULL)
			((t_scene *)scene)->cylinder = ((t_scene *)scene)->cylinder->next;
		((t_scene *)scene)->cylinder->next = newcylinder;
	}
}

void	rt_parse_square(const char **line, void *scene)
{
	t_square	*newsquare;

	newsquare = malloc(sizeof(t_square));
	newsquare->coords = rt_parse_vector(line[1]);
	newsquare->o_vect = rt_parse_vector(line[2]);
	newsquare->side_size = ft_atof(line[3]);
	newsquare->colour = rt_parse_colour(line[4]);
	newsquare->next = NULL;
	if (((t_scene *)scene)->square == NULL)
		((t_scene *)scene)->square = newsquare;
	else
	{
		while (((t_scene *)scene)->square->next != NULL)
			((t_scene *)scene)->square = ((t_scene *)scene)->square->next;
		((t_scene *)scene)->square->next = newsquare;
	}
}

void	rt_parse_triangle(const char **line, void *scene)
{
	t_triangle	*newtriangle;

	newtriangle = malloc(sizeof(t_triangle));
	if (newtriangle == NULL)
		return ;
	newtriangle->coord1 = rt_parse_vector(line[1]);
	newtriangle->coord2 = rt_parse_vector(line[2]);
	newtriangle->coord3 = rt_parse_vector(line[3]);
	newtriangle->colour = rt_parse_colour(line[4]);
	newtriangle->next = NULL;
	if (((t_scene *)scene)->triangle == NULL)
		((t_scene *)scene)->triangle = newtriangle;
	else
	{
		while (((t_scene *)scene)->triangle->next != NULL)
			((t_scene *)scene)->triangle = ((t_scene *)scene)->triangle->next;
		((t_scene *)scene)->triangle->next = newtriangle;
	}
}

void	rt_parse_resolution(const char **line, void *scene)
{
	t_resolution	*res;

	res = malloc(sizeof(t_resolution));
	if (((t_scene *)scene)->resolution != NULL || res == NULL)
		return ;
	res->h = ft_atoi(line[1]);
	res->v = ft_atoi(line[2]);
	((t_scene *)scene)->resolution = res;
}

void	rt_parse_ambient(const char **line, void *scene)
{
	t_ambient	*a;

	a = malloc(sizeof(t_ambient));
	if (((t_scene *)scene)->ambient != NULL || a == NULL)
		return ;
	a->ratio = ft_atof(line[1]);
	a->colour = rt_parse_colour(line[2]);
	((t_scene *)scene)->ambient = a;
}

t_f	*rt_fill_func(t_f *func)
{
	func['\0'] = *rt_parse_ambient;
	func['R' - 'A'] = *rt_parse_resolution;
	func['c' - 'A']	= *rt_parse_camera;
	func['l' - 'A'] = *rt_parse_light;
	func['c' + ('y' % 5) - 'A'] = *rt_parse_cylinder;
	func['p' + ('l' % 5) - 'A'] = *rt_parse_plane;
	func['s' + ('p' % 5) - 'A'] = *rt_parse_sphere;
	func['s' + ('q' % 5) - 'A'] = *rt_parse_square;
	func['t' + ('r' % 5) - 'A'] = *rt_parse_triangle;
	return (func);
}

t_scene	*rt_parse(char *file)
{
	int		fd;
	char	*line;
	char	**split;
	t_f		*func;
	t_scene	*scene;

	fd = open(file, O_RDONLY);
	line = NULL;
	func = malloc(256 * sizeof(t_f));
	scene = ft_calloc(1, sizeof(t_scene));
	if (!func)
		return (scene);
	func = rt_fill_func(func);
	while (get_next_line(fd, &line))
	{
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		split = ft_split(line, ' ');
		(func[split[0][0] + (split[0][1] % 5) - 'A'])((const char **)split, scene);
		rt_freesplit(split);
		free(line);
		line = NULL;
	}
	if (*line == '\0')
	{
		free(func);
		close(fd);
		return (scene);
	}
	split = ft_split(line, ' ');
	(func[split[0][0] + (split[0][1] % 5) - 'A'])((const char **)split, scene);
	free(func);
	rt_freesplit(split);
	free(line);
	close(fd);
	return (scene);
}
