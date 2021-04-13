/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkscene.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 09:48:41 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/12 12:14:03 by mteerlin      ########   odam.nl         */
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
	printf("res:\n\tx: %i\n\ty: %i\n\taspectratio: %lf\n\n", scene->res->h, scene->res->v, scene->res->ratio);
	printf("amb:\n\tratio: %lf\n\tcolor:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", scene->amb->ratio, scene->amb->color->r, scene->amb->color->g, scene->amb->color->b);


	temp = scene->cam;
	i = 1;
	while ((t_camera *)temp != NULL)
	{
		printf("camera: %i\n", i);
		printf("\tcoordinates:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_camera *)temp)->coords->x, ((t_camera *)temp)->coords->y, ((t_camera *)temp)->coords->z);
		printf("\torientation vector:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_camera *)temp)->o_vect->x, ((t_camera *)temp)->o_vect->y, ((t_camera *)temp)->o_vect->z);
		printf("\tfield of view:\t%i\n\n", ((t_camera *)temp)->fov);
		temp = ((t_camera *)temp)->next;
	}
	
	temp = scene->light;
	i = 1;
	while ((t_light *)temp != NULL)
	{
		printf("light: %i\n", i);
		printf("\tcoordinates:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_light *)temp)->coords->x, ((t_light *)temp)->coords->y, ((t_light *)temp)->coords->z);
		printf("\tbrightness: %lf\n", ((t_light *)temp)->lux);
		printf("\tcolor:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", ((t_light *)temp)->color->r, ((t_light *)temp)->color->g, ((t_light *)temp)->color->b);
		temp = ((t_light *)temp)->next;
	}
	

	temp = scene->cy;
	i = 1;
	while ((t_cylinder *)temp != NULL)
	{
		printf("cy: %i\n", i);
		printf("\tcoordinates:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_cylinder *)temp)->coords->x, ((t_cylinder *)temp)->coords->y, ((t_cylinder *)temp)->coords->z);
		printf("\torientation vector:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_cylinder *)temp)->o_vect->x, ((t_cylinder *)temp)->o_vect->y, ((t_cylinder *)temp)->o_vect->z);
		printf("\tdiameter: %lf\n", ((t_cylinder *)temp)->dia);
		printf("\thight: %lf\n", ((t_cylinder *)temp)->hight);
		printf("\tcolor:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", ((t_cylinder *)temp)->color->r, ((t_cylinder *)temp)->color->g, ((t_cylinder *)temp)->color->b);
		temp = ((t_cylinder *)temp)->next;
		i++;
	}
	temp = scene->pl;
	i = 1;
	while ((t_plane *)temp != NULL)
	{
		printf("pl %i:\n", i);
		printf("\tcoordinates:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_plane *)temp)->coords->x, ((t_plane *)temp)->coords->y, ((t_plane *)temp)->coords->z);
		printf("\torientation vector:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_plane *)temp)->o_vect->x, ((t_plane *)temp)->o_vect->y, ((t_plane *)temp)->o_vect->z);
		printf("\tcolor:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", ((t_plane *)temp)->color->r, ((t_plane *)temp)->color->g, ((t_plane *)temp)->color->b);
		temp = ((t_plane *)temp)->next;
		i++;
	}
	temp = scene->sp;
	i = 1;
	while ((t_sphere *)temp)
	{
		printf("sp %i:\n", i);
		printf("\tcoordinates:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_sphere *)temp)->coords->x, ((t_sphere *)temp)->coords->y, ((t_sphere *)temp)->coords->z);
		printf("\tradius: %lf\n", ((t_sphere *)temp)->rad);
		printf("\tcolor:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", ((t_sphere *)temp)->color->r, ((t_sphere *)temp)->color->g, ((t_sphere *)temp)->color->b);
		temp = ((t_sphere *)temp)->next;
		i++;
	}

	temp = scene->sq;
	i = 1;
	while ((t_square *)temp != NULL)
	{	
		printf("sq %i:\n", i);
		printf("\tcoordinates:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_square *)temp)->coords->x, ((t_square *)temp)->coords->y, ((t_square *)temp)->coords->z);
		printf("\torientation vector:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_square *)temp)->o_vect->x, ((t_square *)temp)->o_vect->y, ((t_square *)temp)->o_vect->z);
		printf("\tside size: %lf\n", ((t_square *)temp)->side_size);
		printf("\tcolor:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", ((t_square *)temp)->color->r, ((t_square *)temp)->color->g, ((t_square *)temp)->color->b);
		temp = ((t_square *)temp)->next;
		i++;
	}
	
	temp = scene->tr;
	i = 1;
	while ((t_triangle *)temp != NULL)
	{
		printf("tr %i:\n", i);
		printf("\tcoordinate 1:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_triangle *)temp)->coord1->x, ((t_triangle *)temp)->coord1->y, ((t_triangle *)temp)->coord1->z);
		printf("\tcoordinate 2:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_triangle *)temp)->coord2->x, ((t_triangle *)temp)->coord2->y, ((t_triangle *)temp)->coord2->z);
		printf("\tcoordinate 3:\n\t\tx: %lf\n\t\ty: %lf\n\t\tz: %lf\n", ((t_triangle *)temp)->coord3->x, ((t_triangle *)temp)->coord3->y, ((t_triangle *)temp)->coord3->z);
		printf("\tcolor:\n\t\tr: %i\n\t\tg: %i\n\t\tb: %i\n\n", ((t_triangle *)temp)->color->r, ((t_triangle *)temp)->color->g, ((t_triangle *)temp)->color->b);
		temp = ((t_triangle *)temp)->next;
		i++;
	}
	rt_free_scene(scene);
	return (0);
}
