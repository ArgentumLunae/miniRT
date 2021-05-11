/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sortoutmaths.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/10 13:11:47 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/05/11 16:36:49 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "vmaths.h"
#include <fcntl.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

static void	get_datareq(t_mlx *prog, t_scene *scene)
{
	prog->bpp = 8 * sizeof(int);
	prog->sizel = scene->res->h * scene->res->v;
	prog->end = 1;
}

static int	get_pixel_colour(t_mlx *prog, t_scene *scene)
{
	void	*temp;
	void	*fobj;
	double	t;
	bool	hit;
	int		color;
	int		shade;
	int		obj;

	temp = scene->sp;
	hit = false;
	t = 1 / rt_vect_mag(&scene->cam->rdir, scene->origin);
	scene->cam->rdir = *rt_vect_scale(t, scene->cam->rdir);
	t = DBL_MAX;
	obj = 0;
	while (temp != NULL)
	{
		if (rt_sphere_inter(scene->cam, (t_sphere *)temp, &t))
		{
			fobj = temp;
			obj = 1;
			hit = true;
		}
		temp = ((t_sphere *)temp)->next;
	}
	//printf("t = %lf\n", t);
	temp = scene->pl;
	while (temp != NULL)
	{
		if (rt_plane_inter(scene->cam, (t_plane *)temp, &t))
		{
			fobj = temp;
			obj  = 2;
			hit  = true;
		}
		temp = ((t_plane *)temp)->next;
	}
	temp = scene->tr;
	while (temp != NULL)
	{
		if (rt_tr_intersect(scene->cam, (t_triangle *)temp, &t))
		{
			fobj = temp;
			obj = 3;
			hit = true;
		}
		temp = ((t_triangle *)temp)->next;
	}
	temp = scene->sq;
	while (temp != NULL)
	{
		if	(rt_sq_intersect(scene->cam, (t_square *)temp, scene, &t))
		{
			fobj = temp;
			obj = 4;
			hit = true;
		}
		temp = ((t_square *)temp)->next;
	}
	shade = 0;
	if (hit)
	{
		color = 0;
		if (obj == 1)
		{
			color = (((t_sphere *)fobj)->color->r << 16) + (((t_sphere *)fobj)->color->g << 8) + ((t_sphere *)fobj)->color->b;
			color = mlx_get_color_value(prog->mlx, color);
			scene->cam->rdir = *rt_vect_scale(t, scene->cam->rdir);
			temp = scene->light;
			while (temp != NULL)
			{
				((t_light *)temp)->rdir = rt_vect_sub(&scene->cam->rdir, ((t_light *)temp)->coords);
//				printf("rcam: %lf,%lf,%lf |\trlight: %lf,%lf,%lf\n", scene->cam->rdir.x, scene->cam->rdir.y, scene->cam->rdir.z, scene->light->rdir->x, scene->light->rdir->y, scene->light->rdir->z);
				t = ((t_light *)temp)->lux * rt_light_sp(scene, fobj);
				shade = rt_add_shade(t, color, scene->amb, (t_light *)temp);
				temp = ((t_light *)temp)->next;
			}
		}
		else if (obj == 2)
		{
			color = (((t_plane *)fobj)->color->r << 16) + (((t_plane *)fobj)->color->g << 8) + ((t_plane *)fobj)->color->b;
			color = mlx_get_color_value(prog->mlx, color);
			scene->cam->rdir = *rt_vect_scale(t, scene->cam->rdir);
			temp = scene->light;
			while (temp != NULL)
			{
				((t_light *)temp)->rdir = rt_vect_sub(&scene->cam->rdir, ((t_light *)temp)->coords);
//				printf("rcam: %lf,%lf,%lf |\trlight: %lf,%lf,%lf\n", scene->cam->rdir.x, scene->cam->rdir.y, scene->cam->rdir.z, scene->light->rdir->x, scene->light->rdir->y, scene->light->rdir->z);
				t = ((t_light *)temp)->lux * rt_light_pl(scene, fobj);
				shade = rt_add_shade(t, color, scene->amb, (t_light *)temp);
				temp = ((t_light *)temp)->next;
			}
		}
		else if (obj == 3)
		{
			color = (((t_triangle *)fobj)->color->r << 16) + (((t_triangle *)fobj)->color->g << 8) + ((t_triangle *)fobj)->color->b;
			color = mlx_get_color_value(prog->mlx, color);
			scene->cam->rdir = *rt_vect_scale(t, scene->cam->rdir);
			temp = scene->light;
			while (temp != NULL)
			{
				((t_light *)temp)->rdir = rt_vect_sub(&scene->cam->rdir, ((t_light *)temp)->coords);
//				printf("rcam: %lf,%lf,%lf |\trlight: %lf,%lf,%lf\n", scene->cam->rdir.x, scene->cam->rdir.y, scene->cam->rdir.z, scene->light->rdir->x, scene->light->rdir->y, scene->light->rdir->z);
				t = ((t_light *)temp)->lux * rt_light_tr(scene, fobj);
				shade = rt_add_shade(t, color, scene->amb, (t_light *)temp);
				temp = ((t_light *)temp)->next;
			}
		}
		else if (obj == 4)
		{
			color = (((t_square *)fobj)->color->r << 16) + (((t_square *)fobj)->color->g << 8) + ((t_square *)fobj)->color->b;
			color = mlx_get_color_value(prog->mlx, color);
			scene->cam->rdir = *rt_vect_scale(t, scene->cam->rdir);
			temp = scene->light;
			while (temp != NULL)
			{
				((t_light *)temp)->rdir = rt_vect_sub(&scene->cam->rdir, ((t_light *)temp)->coords);
//				printf("rcam: %lf,%lf,%lf |\trlight: %lf,%lf,%lf\n", scene->cam->rdir.x, scene->cam->rdir.y, scene->cam->rdir.z, scene->light->rdir->x, scene->light->rdir->y, scene->light->rdir->z);
				t = ((t_light *)temp)->lux * rt_light_sq(scene, fobj);
				shade = rt_add_shade(t, color, scene->amb, (t_light *)temp);
				temp = ((t_light *)temp)->next;
			}
		}
		
		return (shade);
	}
	else
		return (mlx_get_color_value(prog->mlx, 0x0));
}

static void	build_image(t_mlx *prog, t_scene *scene)
{
	unsigned int	x;
	unsigned int	y;
	int				datay;
	t_vector		pxl;
	double			phi;

	pxl.z = -1;
	phi = tan(scene->cam->fov / 2 * (M_PI / 180));
	y = 0;
	while (y < scene->res->v)
	{
		pxl.y = (1 - 2 * (y + 0.5) / scene->res->v) * phi;
		datay = scene->res->h * y;
		x = 0;
		while (x < scene->res->h)
		{
			pxl.x = (2 * ((x + 0.5) / scene->res->h) - 1)* scene->res->ratio * phi;
			scene->cam->rdir = *rt_vect_scale(1 / rt_vect_mag(&pxl, scene->origin), pxl);
			((int *)prog->data)[datay + x] = get_pixel_colour(prog, scene);
//			printf("x,y: %i,%i\n", x, y);
			x++;
		}
		y++;
	}
}

int	key_release(int keycode, t_mlx *prog)
{
	printf("keycode:\t%i\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(prog->mlx, prog->win);
		exit(0);
		return (0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	prog;
	t_scene	*scene;

	if (argc < 2)
		return (0);
	scene = rt_parse(argv[1]);
	get_datareq(&prog, scene);
	prog.mlx = mlx_init();
	prog.win = mlx_new_window(prog.mlx, scene->res->h, scene->res->v, "miniRT");
	prog.img = mlx_new_image(prog.mlx, scene->res->h, scene->res->v);
	prog.data = mlx_get_data_addr(prog.img, &prog.bpp, &prog.sizel, &prog.end);
	build_image(&prog, scene);
	mlx_put_image_to_window(prog.mlx, prog.win, prog.img, 0, 0);
	mlx_hook(prog.win, 3, 1L<<1, key_release, &prog);
	mlx_loop(prog.mlx);
	free(scene->light);
	return (0);
}
