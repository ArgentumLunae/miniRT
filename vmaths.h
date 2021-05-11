/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vmaths.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 12:35:01 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/29 17:20:56 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef	VMATHS_H
# define VMATHS_H
# include "minirt.h"

typedef struct s_discriminant
{
	double	a;
	double	b;
	double	c;
	double	d;
}	t_discriminant;

double		rt_vect_dot(t_vector *v1, t_vector *v2);
t_vector	*rt_vect_cross(t_vector *v1, t_vector *v2);
t_vector	*rt_vect_scale(double c, t_vector v);
t_vector	*rt_vect_sub(t_vector *v1, t_vector *v2);
t_vector	*rt_vect_add(t_vector *v1, t_vector *v2);
double		rt_vect_mag(t_vector *v1, t_vector *v2);
t_vector	*rt_vect_dir(t_vector *vs, t_vector *vp);
double		rt_vect_angle(t_vector *v1, t_vector *v2, t_scene *scene);
t_vector	*vect_normalize(t_vector *vs, t_vector *vp);

#endif