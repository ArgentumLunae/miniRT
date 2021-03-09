/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   startparce.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 19:16:49 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/09 19:27:29 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_square
{
	float	coords[3];
	float	o_vect[3];
	int		colour[3];
}				t_square;

typedef struct	s_sphere
{
	float	coords[3];
	float	rad[3];
	int		colour[3];
}				t_sphere;

typedef struct	s_plane
{
	float	coords[3];
	float	o_vect[3];
	int		colour[3];
}				t_plane;

typedef struct	s_cylynder
{
	float	coords[3];
	float	o_vect[3];
	float	dia;
	float	hight;
	int		colour[3];
}				t_cylinder

typedef struct	s_triangle
{
	float	coord1[3];
	float	coord2[3];
	float	coord3[3];
	int		colour[3];
}				t_triangle;