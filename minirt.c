/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 09:48:41 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/01 13:23:10 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include "minirt.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_scene	*scene;
	void	*temp;
	int		i;

	if (argc < 2)
		return (0);
	scene = rt_parse(argv[1]);
	printf("resolution:\n\tx: %i\n\ty: %i\n\n", scene->resolution->h, scene->resolution->v);
	printf("ambient:\n\tratio: %lf\n\tcolour:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", scene->ambient->ratio, scene->ambient->colour->r, scene->ambient->colour->g, scene->ambient->colour->b);

	temp = scene->cylinder;
	i = 1;
	while ((t_cylinder *)temp != NULL)
	{
		printf("cylinder: %i\n", 1);
		printf("\tcoordinates:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_cylinder *)temp)->coords->x, ((t_cylinder *)temp)->coords->y, ((t_cylinder *)temp)->coords->z);
		printf("\torientation vector:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_cylinder *)temp)->o_vect->x, ((t_cylinder *)temp)->o_vect->y, ((t_cylinder *)temp)->o_vect->z);
		printf("\tdiameter: %lf\n", ((t_cylinder *)temp)->dia);
		printf("\thight: %lf\n", ((t_cylinder *)temp)->hight);
		printf("\tcolour:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", ((t_cylinder *)temp)->colour->r, ((t_cylinder *)temp)->colour->g, ((t_cylinder *)temp)->colour->b);
		temp = ((t_cylinder *)temp)->next;
		i++;
	}
	temp = scene->plane;
	i = 1;
	while ((t_plane *)temp != NULL)
	{
		printf("plane %i:\n", 1);
		printf("\tcoordinates:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_plane *)temp)->coords->x, ((t_plane *)temp)->coords->y, ((t_plane *)temp)->coords->z);
		printf("\torientation vector:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_plane *)temp)->o_vect->x, ((t_plane *)temp)->o_vect->y, ((t_plane *)temp)->o_vect->z);
		printf("\tcolour:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", ((t_plane *)temp)->colour->r, ((t_plane *)temp)->colour->g, ((t_plane *)temp)->colour->b);
		temp = ((t_plane *)temp)->next;
		i++;
	}
	temp = scene->sphere;
	i = 1;
	while ((t_sphere *)temp)
	{
		printf("sphere %i:\n", i);
		printf("\tcoordinates:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_sphere *)temp)->coords->x, ((t_sphere *)temp)->coords->y, ((t_sphere *)temp)->coords->z);
		printf("\tradius: %lf\n", ((t_sphere *)temp)->rad);
		printf("\tcolour:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", ((t_sphere *)temp)->colour->r, ((t_sphere *)temp)->colour->g, ((t_sphere *)temp)->colour->b);
		temp = ((t_sphere *)temp)->next;
		i++;
	}

	temp = scene->square;
	i = 1;
	while ((t_square *)temp != NULL)
	{	
		printf("square %i:\n", i);
		printf("\tcoordinates:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_square *)temp)->coords->x, ((t_square *)temp)->coords->y, ((t_square *)temp)->coords->z);
		printf("\torientation vector:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_square *)temp)->o_vect->x, ((t_square *)temp)->o_vect->y, ((t_square *)temp)->o_vect->z);
		printf("\tside size: %lf\n", ((t_square *)temp)->side_size);
		printf("\tcolour:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", ((t_square *)temp)->colour->r, ((t_square *)temp)->colour->g, ((t_square *)temp)->colour->b);
		temp = ((t_square *)temp)->next;
		i++;
	}
	
	temp = scene->triangle;
	i = 1;
	while ((t_triangle *)temp != NULL)
	{
		printf("triangle %i:\n", i);
		printf("\tcoordinate 1:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_triangle *)temp)->coord1->x, ((t_triangle *)temp)->coord1->y, ((t_triangle *)temp)->coord1->z);
		printf("\tcoordinate 2:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_triangle *)temp)->coord2->x, ((t_triangle *)temp)->coord2->y, ((t_triangle *)temp)->coord2->z);
		printf("\tcoordinate 3:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_triangle *)temp)->coord3->x, ((t_triangle *)temp)->coord3->y, ((t_triangle *)temp)->coord3->z);
		printf("\tcolour:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", ((t_triangle *)temp)->colour->r, ((t_triangle *)temp)->colour->g, ((t_triangle *)temp)->colour->b);
		temp = ((t_triangle *)temp)->next;
		i++;
	}
	rt_free_scene(scene);
	return (0);
}
