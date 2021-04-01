/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 09:48:41 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/29 16:07:37 by mteerlin      ########   odam.nl         */
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
	printf("ambient:\n\tratio: %lf\n\tcolour:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", scene->ambient->ratio, scene->ambient->colour.r, scene->ambient->colour.g, scene->ambient->colour.b);
	
	printf("cylinder:\n");
	printf("\tcoordinates:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", scene->cylinder->coords.x, scene->cylinder->coords.y, scene->cylinder->coords.z);
	printf("\torientation vector:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", scene->cylinder->o_vect.x, scene->cylinder->o_vect.y, scene->cylinder->o_vect.z);
	printf("\tdiameter: %lf\n", scene->cylinder->dia);
	printf("\thight: %lf\n", scene->cylinder->hight);
	printf("\tcolour:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", scene->cylinder->colour.r, scene->cylinder->colour.g, scene->cylinder->colour.b);
	
	printf("plane:\n");
	printf("\tcoordinates:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", scene->plane->coords.x, scene->plane->coords.y, scene->plane->coords.z);
	printf("\torientation vector:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", scene->plane->o_vect.x, scene->plane->o_vect.y, scene->plane->o_vect.z);
	printf("\tcolour:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", scene->plane->colour.r, scene->plane->colour.g, scene->plane->colour.b);

	printf("sphere:\n");
	printf("\tcoordinates:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", scene->sphere->coords.x, scene->sphere->coords.y, scene->sphere->coords.z);
	printf("\tradius: %lf\n", scene->sphere->rad);
	printf("\tcolour:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", scene->sphere->colour.r, scene->sphere->colour.g, scene->sphere->colour.b);

	printf("square:\n");
	printf("\tcoordinates:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", scene->square->coords.x, scene->square->coords.y, scene->square->coords.z);
	printf("\torientation vector:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", scene->square->o_vect.x, scene->square->o_vect.y, scene->square->o_vect.z);
	printf("\tside size: %lf\n", scene->square->side_size);
	printf("\tcolour:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", scene->square->colour.r, scene->square->colour.g, scene->square->colour.b);
	
	temp = scene->triangle;
	i = 1;
	while ((t_triangle *)temp != NULL)
	{
		printf("triangle %i:\n", i);
		printf("\tcoordinate 1:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_triangle *)temp)->coord1.x, ((t_triangle *)temp)->coord1.y, ((t_triangle *)temp)->coord1.z);
		printf("\tcoordinate 2:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_triangle *)temp)->coord2.x, ((t_triangle *)temp)->coord2.y, ((t_triangle *)temp)->coord2.z);
		printf("\tcoordinate 3:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_triangle *)temp)->coord3.x, ((t_triangle *)temp)->coord3.y, ((t_triangle *)temp)->coord3.z);
		printf("\tcolour:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", ((t_triangle *)temp)->colour.r, ((t_triangle *)temp)->colour.g, ((t_triangle *)temp)->colour.b);
		temp = ((t_triangle *)temp)->next;
		i++;
	}
	rt_free_scene(scene);
	return (0);
}
