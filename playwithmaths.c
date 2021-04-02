/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   playwithmaths.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/30 10:50:44 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/02 15:18:03 by mteerlin      ########   odam.nl         */
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
#include <float.h>

double	vectordot(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector	vectorscale(double s, t_vector *v)
{
	t_vector svect;

	svect.x = s * v->x;
	svect.y = s * v->y;
	svect.z = s * v->z;

	return (svect);
}

t_vector	rt_vector_sub(t_vector *v1, t_vector *v2)
{
	t_vector	vsub;

	vsub.x = v1->x - v2->x;
	vsub.y = v1->y - v2->y;
	vsub.z = v1->z - v2->z;
	return (vsub);
}

t_vector	rt_raydir(t_vector *vs, t_vector *vp)
{
	t_vector	dir;
	double		largest;
	double		xl;
	double 		yl;
	double		zl;

	dir = rt_vector_sub(vp, vs);
	xl = fabs(dir.x);
	yl = fabs(dir.y);
	zl = fabs(dir.z);
	largest = xl;
	if (yl > largest)
		largest = yl;
	if (zl > largest)
		largest = zl;
	dir.x /= largest;
	dir.y /= largest;
	dir.z /= largest;

	return (dir);
}

bool	raysphere(t_ray *r, t_sphere *s, double *t)
{
	bool		ret;
	double		a, b, c, d;
	double		tzero, tone, sqrtd;
	t_vector	dist;

	ret = false;
	//ft_putstr_fd("direction:", 1);
	//ft_putnbr_fd(r->dir.x, 1);
	//ft_putnbr_fd(r->dir.y, 1);
	//ft_putnbr_fd(r->dir.z, 1);
	//ft_putchar_fd('\t', 1);
	//ft_putstr_fd("start:", 1);
	//ft_putnbr_fd(r->start.x, 1);
	//ft_putchar_fd(',', 1);
	//ft_putnbr_fd(r->start.y, 1);
	//ft_putchar_fd('\t', 1);

	a = vectordot(&r->dir, &r->dir);
	dist = rt_vector_sub(&r->start, s->coords);
	b = 2 * vectordot(&r->dir, &dist);
	c = vectordot(&dist, &dist) - (s->rad * s->rad);
	d = b * b - 4 * a * c;
	//printf("%lf\t", d);
	if (d < 0)
		ret = false;
	else
	{
		//printf("hit %lf\t", d);
		sqrtd = sqrt(d);
		tzero = (-b + sqrtd) / (2 * a);
		tone = (-b + sqrtd) / (2 * a);
		if (tzero > tone)
			tzero = tone;
		if (tzero > 0.0001 && tzero < *t)
		{
			//printf("\t%lf\t", tzero);
			*t = tzero;
			ret = true;
		}
		else
			ret = false;
	}
	return (ret);
}

t_vector	*rt_vector_scale(double c, t_vector *v)
{
	t_vector	*ret;

	ret = malloc(sizeof(t_vector));
	ret->x = c * v->x;
	ret->y = c * v->y;
	ret->z = c * v->z;
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

double	rt_vector_length(t_vector *v1, t_vector *v2)
{
	t_vector t;
	double	temp;
	double length;

	t = rt_vector_sub(v1, v2);
	temp = sqrt((t.x * t.x) + (t.y * t.y));
	length = sqrt(temp * temp + t.z *t.z);
	return (length);
}

int	rt_add_shade(double distance, int colour)
{
	int r;
	int g;
	int b;
	
	b = (1-distance) * (colour % 256);
	g = (1-distance) * ((colour << 8) % 256);
	r = (1-distance) * ((colour << 16) % 256);

	return((r << 16) + (g << 8) + b);
}

int	main(void)
{
	t_mlx			program;
	t_scene			*scene;
	t_sphere		*temp;
	t_light			*templ;
	t_sphere		*sphit;
	t_ray			ray;
	t_ray			lightray;
	t_vector		intersect;
	unsigned int	x;
	unsigned int	y;
	int				bpp, sizeline, endian, colour;
	double			t, tl;
	bool			hit;
	bool			lit;

	scene = rt_parse("/home/mteerlin/Documents/Codam/Project_miniRT/miniRT_Codam/scene.rt");
	scene->light = malloc(sizeof(t_light));
	scene->light->coords = malloc(sizeof(t_vector));
	scene->light->coords->x = 640;
	scene->light->coords->y = 360;
	scene->light->coords->z = 0;
	scene->light->next = NULL;
	ray.dir.x = 0;
	ray.dir.y = 0;
	ray.dir.z = 1;
	ray.start.z = 0;
	y = 0;
	bpp = 24;
	sizeline = scene->resolution->h * scene->resolution->v;
	endian = 1;
	program.mlx = mlx_init();
	program.win = mlx_new_window(program.mlx, scene->resolution->h, scene->resolution->v, "sphere");
	program.img = mlx_new_image(program.mlx, scene->resolution->h, scene->resolution->v);
	program.data = mlx_get_data_addr(program.img, &bpp, &sizeline, &endian);
	while (y < scene->resolution->v)
	{
		ray.start.y = y;
		x = 0;
		while (x < scene->resolution->h)
		{
			hit = false;
			ray.start.x = x;
			temp = scene->sphere;
			sphit = scene->sphere;
			t = DBL_MAX;
			while (temp)
			{
				if (raysphere(&ray, temp, &t))
				{
					hit = true;
					sphit = temp;
				}
				temp = temp->next;
			}	
			//ft_putchar_fd('\t', 1);
			if (hit == true)
			{
				//ft_putstr_fd("hit\t", 1);
				templ = scene->light;
				intersect = rt_vector_add(&ray.start, rt_vector_scale(t, &ray.dir));
				while (templ)
				{
					lightray.start = intersect;
					lightray.dir = rt_raydir(&lightray.start, scene->light->coords);
					//printf("%lf,%lf,%lf\t", lightray.dir.x, lightray.dir.y, lightray.dir.z);
					temp = scene->sphere;
					tl = rt_vector_length(&lightray.start, scene->light->coords);
					lit = true;
					while (temp)
					{
						if (raysphere(&lightray, temp, &tl))
							lit = false;
						temp = temp->next;
					}
					templ = templ->next;
				}
				if (lit == true)
				{
					//printf("%lf\t", tl);
					colour = mlx_get_color_value(program.mlx, (sphit->colour->r << 16) + (sphit->colour->g << 8) + (sphit->colour->b));
					//colour = rt_add_shade(((1/sqrt(tl))), colour);
					((int *)program.data)[x + (scene->resolution->h * y)] = colour;
				}
				else
				{
					colour = mlx_get_color_value(program.mlx, (sphit->colour->r << 16) + (sphit->colour->g << 8) + (sphit->colour->b));
					colour = rt_add_shade((0.5), colour);
					((int *)program.data)[x + (scene->resolution->h * y)] = colour;
				}
			}
			else
			{
				if (ray.start.x == scene->light->coords->x && ray.start.y == scene->light->coords->y)
					colour = mlx_get_color_value(program.mlx, (255 << 16) + (255 << 8) + (255));
				else
					colour = mlx_get_color_value(program.mlx, (127 << 16) + (127 << 8) + (127));
				((int *)program.data)[x + (scene->resolution->h * y)] = colour;
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(program.mlx, program.win, program.img, 0, 0);
	mlx_loop(program.mlx);
	free(scene->light);
	return (0);
}
