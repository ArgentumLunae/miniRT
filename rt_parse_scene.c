/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_parse_scene.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:55:05 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/09 18:22:39 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

t_f	*rt_fill_func(t_f *func)
{
	func['\0'] = *rt_parse_ambient;
	func['R' - 'A'] = *rt_parse_resolution;
	func['c' - 'A'] = *rt_parse_camera;
	func['l' - 'A'] = *rt_parse_light;
	func['c' + ('y' % 5) - 'A'] = *rt_parse_cylinder;
	func['p' + ('l' % 5) - 'A'] = *rt_parse_plane;
	func['s' + ('p' % 5) - 'A'] = *rt_parse_sphere;
	func['s' + ('q' % 5) - 'A'] = *rt_parse_square;
	func['t' + ('r' % 5) - 'A'] = *rt_parse_triangle;
	return (func);
}

static t_vector	*define_origin(void)
{
	t_vector	*origin;

	origin = malloc(sizeof(t_vector));
	if (!origin)
		return (NULL);
	origin->x = 0;
	origin->y = 0;
	origin->z = 0;
	return (origin);
}

void	rt_parse_line(char *line, t_scene *scene, int eof)
{
	static t_f	*func;
	char		**split;

	if (!func)
	{
		func = ft_calloc(256, sizeof(t_f));
		if (!func)
			return ;
		func = rt_fill_func(func);
	}
	if (*line == '\0')
	{
		free(line);
		if (eof != 0)
			free(func);
		return ;
	}
	split = ft_split(line, ' ');
	(func[split[0][0] + (split[0][1] % 5) - 'A'])((const char **)split, scene);
	rt_freesplit(split);
	free(line);
	line = NULL;
	if (eof != 0)
		free(func);
}

t_scene	*rt_parse(char *file)
{
	int		fd;
	char	*line;
	t_scene	*scene;

	fd = open(file, O_RDONLY);
	line = NULL;
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->origin = define_origin();
	if (!scene->origin)
		return (scene);
	while (get_next_line(fd, &line))
		rt_parse_line(line, scene, 0);
	rt_parse_line(line, scene, 0);
	close(fd);
	return (scene);
}
