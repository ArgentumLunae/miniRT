/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   playwithmaths.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/30 10:50:44 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/06 20:10:36 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <fcntl.h>
#include <float.h>
#include "vmaths.h"

bool	raysphere(t_ray *r, t_sphere *s, double *t)
{
	bool		ret;
	double		a, b, c, d;
	double		tzero, tone, sqrtd;
	t_vector	dist;

	ret = false;
	a = rt_vector_dot(r->dir, r->dir);
	dist = rt_vector_sub(r->start, s->coords);
	b = 2 * rt_vector_dot(r->dir, &dist);
	c = rt_vector_dot(&dist, &dist) - (s->rad * s->rad);
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
		if (tzero > 0.0001 && tzero < *t)
		{
			*t = tzero;
			ret = true;
		}
		else
			ret = false;
	}
	return (ret);
}

int	rt_add_shade(double distance, int colour)
{
	int	r;
	int	g;
	int	b;

	b = (1 - distance) * (colour % 256);
	g = (1 - distance) * ((colour << 8) % 256);
	r = (1 - distance) * ((colour << 16) % 256);
	return ((r << 16) + (g << 8) + b);
}

int	main(int argc, char **argv)
{
	t_mlx			program;
	int				bpp;
	int				sizeline;
	int				endian;
	int	x, y;
	double			t;
	int				colour;
	double			aspratio;
	double			camwidth;
	double			px;
	double			py;
	t_sphere		*temp;
	t_sphere		*hitspere;
	t_scene			*scene;
	t_vector		base;
	t_ray			*ray;
	bool			hit;

	if (argc < 2)
		return (0);
	scene = rt_parse(argv[1]);
	bpp = 8 * sizeof(int);
	sizeline = scene->resolution->h * scene->resolution->v;
	endian = 1;
	aspratio = scene->resolution->h / scene->resolution->v;
	camwidth = 2 * aspratio;
	program.mlx = mlx_init();
	program.win = mlx_new_window(program.mlx, scene->resolution->h, scene->resolution->v, "sphere");
	program.img = mlx_new_image(program.mlx, scene->resolution->h, scene->resolution->v);
	program.data = mlx_get_data_addr(program.img, &bpp, &sizeline, &endian);
	base.x = 0;
	base.y = 0;
	base.z = 1;
	y = 0;
	printf("initializing ray?\n");
	ray = malloc(sizeof(t_ray));
	ray->start = scene->camera->coords;
	ray->dir = malloc(sizeof(t_vector));
	ray->dir->z = -1;
	while (y < scene->resolution->v)
	{
		py = (1 - 2 * ((y + 0.5) / scene->resolution->v)) * tan((scene->camera->fov / 2) * (M_PI / 180));
		ray->dir->y = py;
		x = 0;
		t = INT_MAX;
		while (x < scene->resolution->h)
		{
			px = (2 * ((x + 0.5) / scene->resolution->h) - 1) * tan((scene->camera->fov / 2) * (M_PI / 180)) * aspratio;
			ray->dir->x = px;
			temp = scene->sphere;
			hit = false;
			colour = 0;
			while (temp)
			{
				if (raysphere(ray, temp, &t))
				{
					hitspere = temp;
					hit = true;
				}
				temp = temp->next;
			}
			//printf("%lf\n", t);
			if (hit)
			{
				printf("hit\n");
				colour = mlx_get_color_value(program.mlx, (hitspere->colour->r << 24) + (hitspere->colour->g << 18) + hitspere->colour->b);
				((int *)program.data)[(scene->resolution->v * y) + x] = colour;
			}
			else
			{
				colour = mlx_get_color_value(program.mlx, (127 << 24) + (127 << 18) + 127);
				((int *)program.data)[(scene->resolution->v * y) + x] = colour;
			}
			x++;
		}
		printf("%u\n", y);
		y++;
	}
	mlx_put_image_to_window(program.mlx, program.win, program.img, 0, 0);
	mlx_loop(program.mlx);
	free(scene->light);
	return (0);
}
