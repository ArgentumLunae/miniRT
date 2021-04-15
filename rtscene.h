/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rtscene.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 11:04:18 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/13 17:11:18 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTSCENE_H
# define RTSCENE_H

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_ray
{
	t_vector	*start;
	t_vector	*dir;
}	t_ray;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_resolution
{
	unsigned int	h;
	unsigned int	v;
	double			ratio;
}	t_resolution;

typedef struct s_ambient
{
	double	ratio;
	t_rgb	*color;
}	t_ambient;

typedef struct s_light
{
	t_vector		*coords;
	double			lux;
	t_rgb			*color;
	t_vector		*rdir;
	struct s_light	*next;
}	t_light;

typedef struct s_camera
{
	t_vector		*coords;
	t_vector		*o_vect;
	int				fov;
	t_vector		rdir;
	struct s_camera	*next;
}	t_camera;

typedef struct s_square
{
	t_vector		*coords;
	t_vector		*o_vect;
	double			side_size;
	t_rgb			*color;
	struct s_square	*next;
}				t_square;

typedef struct s_sphere
{
	t_vector		*coords;
	double			rad;
	t_rgb			*color;
	struct s_sphere	*next;
}				t_sphere;

typedef struct s_plane
{
	t_vector		*coords;
	t_vector		*o_vect;
	t_rgb			*color;
	struct s_plane	*next;
}				t_plane;

typedef struct s_cylinder
{
	t_vector			*coords;
	t_vector			*o_vect;
	double				dia;
	double				hight;
	t_rgb				*color;
	struct s_cylinder	*next;
}				t_cylinder;

typedef struct s_triangle
{
	t_vector			*coord1;
	t_vector			*coord2;
	t_vector			*coord3;
	t_vector			*vone;
	t_vector			*vtwo;
	t_vector			*vthree;
	t_vector			*norm;
	t_rgb				*color;
	struct s_triangle	*next;
}				t_triangle;

typedef struct s_scene
{
	t_vector		*origin;
	t_resolution	*res;
	t_ambient		*amb;
	t_camera		*cam;
	t_light			*light;
	t_square		*sq;
	t_sphere		*sp;
	t_plane			*pl;
	t_cylinder		*cy;
	t_triangle		*tr;
}	t_scene;

t_scene	*rt_parse(char *file);
void	rt_free_scene(t_scene *scene);

#endif