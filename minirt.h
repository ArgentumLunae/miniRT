/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 11:04:18 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/06 20:11:06 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdbool.h>

typedef void	(*t_f)(const char**, void*);

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*data;
}	t_mlx;

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
}	t_resolution;

typedef struct s_ambient
{
	double	ratio;
	t_rgb	*colour;
}	t_ambient;

typedef struct s_light
{
	t_vector		*coords;
	double			lux;
	t_rgb			*colour;
	struct s_light	*next;
}	t_light;

typedef struct s_camera
{
	t_vector		*coords;
	t_vector		*o_vect;
	int				fov;
	struct s_camera	*next;
}	t_camera;

typedef struct s_square
{
	t_vector		*coords;
	t_vector		*o_vect;
	double			side_size;
	t_rgb			*colour;
	struct s_square	*next;
}				t_square;

typedef struct s_sphere
{
	t_vector		*coords;
	double			rad;
	t_rgb			*colour;
	struct s_sphere	*next;
}				t_sphere;

typedef struct s_plane
{
	t_vector		*coords;
	t_vector		*o_vect;
	t_rgb			*colour;
	struct s_plane	*next;
}				t_plane;

typedef struct s_cylinder
{
	t_vector			*coords;
	t_vector			*o_vect;
	double				dia;
	double				hight;
	t_rgb				*colour;
	struct s_cylinder	*next;
}				t_cylinder;

typedef struct s_triangle
{
	t_vector			*coord1;
	t_vector			*coord2;
	t_vector			*coord3;
	t_rgb				*colour;
	struct s_triangle	*next;
}	t_triangle;

typedef struct s_scene
{
	t_resolution	*resolution;
	t_ambient		*ambient;
	t_camera		*camera;
	t_light			*light;
	t_square		*square;
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	t_triangle		*triangle;
}	t_scene;

t_scene	*rt_parse(char *file);
void	rt_free_scene(t_scene *scene);

#endif