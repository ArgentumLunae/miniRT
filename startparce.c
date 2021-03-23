/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   startparce.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 19:16:49 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/23 18:05:13 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include "minirt.h"
#include "libft.h"
#include <stdlib.h>

t_vector	rt_parse_vector(const char *str)
{
	t_vector	coords;
	char		**split;

	split = ft_split(str, ',');
	coords.x = ft_atof(split[0]);
	coords.y = ft_atof(split[1]);
	coords.z = ft_atof(split[2]);
	return (coords);
}

t_rgb	rt_parse_colour(const char *str)
{
	t_rgb	colour;
	char	**split;

	split = ft_split(str, ',');
	colour.r = ft_atoi(split[0]);
	colour.g = ft_atoi(split[1]);
	colour.b = ft_atoi(split[2]);
	return (colour);
}

void	rt_parse_sphere(const char **line, void *scene)
{
	t_sphere	*temp;
	t_sphere	newsphere;

	temp = ((t_scene *)scene)->sphere;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = &newsphere;
	newsphere.coords = rt_parse_vector(line[1]);
	newsphere.rad = ft_atof(line[2]);
	newsphere.colour = rt_parse_colour(line[3]);
	newsphere.next = NULL;
}

void	rt_parse_plane(const char **line, void *scene)
{
	t_plane	*temp;
	t_plane	newplane;

	temp = ((t_scene *)scene)->plane;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = &newplane;
	newplane.coords = rt_parse_vector(line[1]);
	newplane.o_vect = rt_parse_vector(line[2]);
	newplane.colour = rt_parse_colour(line[3]);
	newplane.next = NULL;
}

void	rt_parse_cylinder(const char **line, void *scene)
{
	t_cylinder	*temp;
	t_cylinder	newcylinder;

	temp = ((t_scene *)scene)->cylinder;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = &newcylinder;
	newcylinder.coords = rt_parse_vector(line[1]);
	newcylinder.o_vect = rt_parse_vector(line[2]);
	newcylinder.dia = ft_atof(line[3]);
	newcylinder.hight = ft_atof(line[4]);
	newcylinder.colour = rt_parse_colour(line[5]);
	newcylinder.next = NULL;
}

void	rt_parse_square(const char **line, void *scene)
{
	t_square	*temp;
	t_square	newsquare;

	temp = ((t_scene *)scene)->square;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = &newsquare;
	newsquare.coords = rt_parse_vector(line[1]);
	newsquare.o_vect = rt_parse_vector(line[2]);
	newsquare.side_size = ft_atof(line[3]);
	newsquare.colour = rt_parse_colour(line[4]);
	newsquare.next = NULL;
}

void	rt_parse_triangle(const char **line, void *scene)
{
	t_triangle	*temp;
	t_triangle	newtriangle;

	temp = ((t_scene *)scene)->triangle;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = &newtriangle;
	newtriangle.coord1 = rt_parse_vector(line[1]);
	newtriangle.coord2 = rt_parse_vector(line[2]);
	newtriangle.coord3 = rt_parse_vector(line[3]);
	newtriangle.colour = rt_parse_colour(line[4]);
	newtriangle.next = NULL;
}

void	rt_parse_resolution(const char **line, void *scene)
{
	t_resolution res;

	if (((t_scene *)scene)->resolution != NULL)
		return;
	res.h = ft_atoi(line[1]);
	res.v = ft_atoi(line[2]);
	((t_scene *)scene)->resolution = &res;
}

void	rt_parse_ambient(const char **line, void *scene)
{
	t_ambient	a;

	if (((t_scene *)scene)->ambient != NULL)
		return ;
	a.ratio = ft_atof(line[1]);
	a.colour = rt_parse_colour(line[2]);
	((t_scene *)scene)->ambient = &a;
}

typedef void (*func)(const char**, void*);

t_f	*rt_fill_func(t_f func[256])
{
	func['\0'] = *rt_parse_ambient;
	func['R' - 'A' + '\0'] = *rt_parse_resolution;
	func['c' + 'y' - 'A'] = *rt_parse_cylinder;
	func['p' + 'l' - 'A'] = *rt_parse_plane;
	func['s' + 'p' - 'A'] = *rt_parse_sphere;
	func['s' + 'q' - 'A'] = *rt_parse_square;
	func['t' + 'r' - 'A'] = *rt_parse_triangle;
	return (func);
}

t_scene	rt_parse(char *file)
{
	int		fd;
	int		i;
	char	*line;
	char	**split;
	t_f		*func;
	t_scene	scene;

	fd = open(file, O_RDONLY);
	line = NULL;
	i = 0;
	func = malloc(256 * sizeof(t_f));
	func = rt_fill_func(func);
	while (get_next_line(fd, &line))
	{
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		split = ft_split(line, ' ');
		(func[split[0][0] + split[0][1] - 'A'])((const char **)split, &scene);
	}
	free(func);
	return (scene);
}
