/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sortoutmaths.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/10 13:11:47 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/12 14:53:45 by mteerlin      ########   odam.nl         */
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
	temp = scene->pl;
	while (temp != 0)
	{
		if (rt_plane_inter(scene->cam, (t_plane *)temp, &t))
		{
			fobj = temp;
			obj  = 2;
			hit  = true;
		}
		temp = ((t_plane *)temp)->next;
	}
	if (hit && obj == 1)
	{
		color = (((t_sphere *)fobj)->color->r << 16) + (((t_sphere *)fobj)->color->g << 8) + ((t_sphere *)fobj)->color->b;
		color = mlx_get_color_value(prog->mlx, color);
		scene->cam->rdir = *rt_vect_scale(t, scene->cam->rdir);
		scene->light->rdir = rt_vect_sub(&scene->cam->rdir, scene->light->coords);
//		printf("rcam: %lf,%lf,%lf |\trlight: %lf,%lf,%lf\n", scene->cam->rdir.x, scene->cam->rdir.y, scene->cam->rdir.z, scene->light->rdir->x, scene->light->rdir->y, scene->light->rdir->z);
		t = scene->amb->ratio + (1 - scene->amb->ratio) * rt_light_angle(scene, fobj);
		return (rt_add_shade(t, color, scene));
	}
	else if (hit && obj == 2)
	{
		color = (((t_plane *)fobj)->color->r << 16) + (((t_plane *)fobj)->color->g << 8) + ((t_plane *)fobj)->color->b;
		color = mlx_get_color_value(prog->mlx, color);
		scene->cam->rdir = *rt_vect_scale(t, scene->cam->rdir);
		scene->light->rdir = rt_vect_sub(&scene->cam->rdir, scene->light->coords);
//		printf("rcam: %lf,%lf,%lf |\trlight: %lf,%lf,%lf\n", scene->cam->rdir.x, scene->cam->rdir.y, scene->cam->rdir.z, scene->light->rdir->x, scene->light->rdir->y, scene->light->rdir->z);
		t = scene->amb->ratio + (1 - scene->amb->ratio) * rt_light_angle(scene, fobj);
		return (rt_add_shade(t, color, scene));
	}
	else
		return (mlx_get_color_value(prog->mlx, 0x808080));
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
	y = 1;
	while (y <= scene->res->v)
	{
		pxl.y = (1 - 2 * (y + 0.5) / scene->res->v) * phi;
		datay = scene->res->h * y;
		x = 1;
		while (x <= scene->res->h)
		{
			pxl.x = (2 * ((x + 0.5) / scene->res->h) - 1)* scene->res->ratio * phi;
			scene->cam->rdir = pxl;
			((int *)prog->data)[datay + x] = get_pixel_colour(prog, scene);
			x++;
		}
		y++;
	}
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
	mlx_loop(prog.mlx);
	free(scene->light);
	return (0);
}
