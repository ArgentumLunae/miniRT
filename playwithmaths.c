/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   playwithmaths.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/30 10:50:44 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/30 17:03:28 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>

double	vectordot(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector	vectorsub(t_vector *v1, t_vector *v2)
{
	t_vector	vsub;

	vsub.x = v1->x - v2->x;
	vsub.y = v1->y - v2->y;
	vsub.z = v1->z - v2->z;
	return (vsub);
}

bool	raysphere(t_ray *r, t_sphere *s, double *t)
{
	bool		ret;
	double		a, b, c, d;
	double		tzero, tone, sqrtd;
	t_vector	dist;

	ret = false;
	a = vectordot(&r->dir, &r->dir);
	dist = vectorsub(&r->start, &s->coords);
	b = 2 * vectordot(&r->dir, &dist);
	c = vectordot(&dist, &dist) - (s->rad * s->rad);
	d = b * b - 4 * a * c;
	if (d < 0)
		ret = false;
	else
	{
		sqrtd = sqrt(d);
		tzero = (-b + sqrtd) / (2 * a);
		tone = (-b + sqrtd) / (2 * a);
		if (tzero > tone)
			tzero = tone;
		if (tzero > 0.001 && tzero < *t)
		{
			*t = tzero;
			ret = true;
		}
		else
			ret = false;
	}
	return (ret);
}

t_vector	rt_vector_scale(double c, t_vector *v)
{
	t_vector	ret;

	ret.x = c * v->x;
	ret.y = c * v->y;
	ret.z = c * v->z;
	return (ret);
}

t_vector	rt_vector_add(t_vector *v1, t_vector *v2)
{
	t_vector	res;

	res.x = v1->x + v2->x;
	res.y = v1->y + v2->y;
	res.z = v1->z + v2->z;
	return (res);
}

int	main(void)
{
	t_mlx			program;
	t_scene			scene;
	t_sphere		*temp;
	t_ray			ray;
	t_resolution	res;
	unsigned int	x;
	unsigned int	y;
	int				bpp, sizeline, endian, colour;
	double			t;
	bool			hit;

	scene.resolution->h = 640;
	scene.resolution->v = 360;
	rt_parse("scene.rt");
	scene.light = malloc(sizeof(t_light));
	scene.light->coords.x = 400;
	scene.light->coords.y = 400;
	scene.light->coords.z = 20;
	ft_putstr_fd("parsed scene\t", 1);
	y = 0;
	bpp = 24;
	sizeline = scene.resolution->h * scene.resolution->v;
	endian = 1;
	program.mlx = mlx_init();
	program.win = mlx_new_window(program.mlx, res.h, res.v, "sphere");
	program.img = mlx_new_image(program.mlx, res.h, res.v);
	program.data = mlx_get_data_addr(program.img, &bpp, &sizeline, &endian);
	ft_putstr_fd("pre loops\t", 1);
	while (y < scene.resolution->v)
	{
		ft_putstr_fd("start line\t", 1);
		ray.start.y = y;
		x = 0;
		while (x < scene.resolution->h)
		{
			printf("%i\t", scene.resolution->h);
			ray.start.x = x;
			temp = scene.sphere;
			while (temp)
			{	
				ft_putstr_fd("check sphere\t", 1);
				hit = raysphere(&ray, temp, &t);
				temp = temp->next;
			}
			if (hit == true)
			{
				colour = mlx_get_color_value(program.mlx, (scene.sphere->colour.r << 16) + (scene.sphere->colour.g << 8) + (scene.sphere->colour.b));
				((int *)program.data)[x + (res.h * y)] = colour;
			}
			else
			{
				colour = mlx_get_color_value(program.mlx, (127 << 16) + (127 << 8) + (127));
				((int *)program.data)[x + (res.h * y)] = colour;
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(program.mlx, program.win, program.img, 0, 0);
	mlx_loop(program.mlx);
	free(scene.light);
	return (0);
}
