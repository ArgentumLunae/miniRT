/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 17:04:58 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/13 17:28:30 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "rtscene.h"
# include <stdbool.h>

typedef void	(*t_f)(const char**, void*);

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*data;
	int			bpp;
	int			sizel;
	int			end;
}	t_mlx;

t_vector	*rt_parse_vector(const char *str);
t_rgb		*rt_parse_colour(const char *str);
void		rt_parse_resolution(const char **line, void *scene);
void		rt_parse_ambient(const char **line, void *scene);
void		rt_parse_camera(const char **line, void *scene);
void		rt_parse_cylinder(const char **line, void *scene);
void		rt_parse_light(const char **line, void *scene);
void		rt_parse_plane(const char **line, void *scene);
void		rt_parse_sphere(const char **line, void *scene);
void		rt_parse_square(const char **line, void *scene);
void		rt_parse_triangle(const char **line, void *scene);

void		rt_free_scene(t_scene *scene);
void		rt_freecam(t_camera *c);
void		rt_freecy(t_cylinder *cy);
void		rt_freel(t_light *l);
void		rt_freepl(t_plane *pl);
void		rt_freesp(t_sphere *sp);
void		rt_freesq(t_square *sq);
void		rt_freetr(t_triangle *tr);
void		rt_freesplit(char **split);

bool		rt_sphere_inter(t_camera *c, t_sphere *s, double *t);
bool		rt_plane_inter(t_camera *cam, t_plane *pl, double *t);
bool	rt_tr_intersect(t_camera *cam, t_triangle *tr, double *t);
double		rt_light_angle(t_scene *scene, t_sphere *fsp);

int	rt_add_shade(double distance, int color, t_ambient *amb, t_light *light);

#endif