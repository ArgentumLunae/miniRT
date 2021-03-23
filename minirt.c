/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/23 09:48:41 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/23 17:30:40 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include "minirt.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_scene scene;

	if (argc < 2)
		return (0);
	scene = rt_parse(argv[1]);
	printf("resolution:\n\tx: %i\n\ty: %i\n\n", scene.resolution->h, scene.resolution->v);
	printf("ambient:\n\tratio: %lf\n\tcolour:\n\tr: %i\n\tg: %i\n\tb: %i\n\n", scene.ambient->ratio, scene.ambient->colour.r, scene.ambient->colour.g, scene.ambient->colour.b);
	return (0);
}
