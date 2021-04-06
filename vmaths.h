/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vmaths.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 12:35:01 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/06 12:40:12 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef	VMATHS_H
# define VMATHS_H
# include "minirt.h"

double		rt_vector_dot(t_vector *v1, t_vector *v2);
t_vector	*rt_vector_scale(double c, t_vector v);
t_vector	rt_vector_sub(t_vector *v1, t_vector *v2);
t_vector	rt_vector_add(t_vector *v1, t_vector *v2);
double		rt_vector_mag(t_vector *v1, t_vector *v2);
t_vector	*rt_vector_dir(t_vector *vs, t_vector *vp);

#endif
