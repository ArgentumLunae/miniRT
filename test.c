/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 10:22:27 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/09 14:06:53 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_opengl_20191021/mlx.h"
#include <math.h>
#include <stdio.h>

int main(void)
{
	void *mlx_ptr;
	void *win_ptr;
	int i;
	int j;
	float r;
	float g;
	float b;

	i = 0;
	j = 0;
	printf("Colour integer: %f\n", (r * pow(2, 16)));
	printf("Colour integer: %f\n", (g * pow(2, 8)));
	printf("Colour integer: %f\n", b);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 510, 510, "Charles Charlemaine");
	while (i < 256)
	{
		j = 0;
		while (j < 256)
		{
			r = i;
			g = j;
			b = 255 - i;
			mlx_pixel_put(mlx_ptr, win_ptr, 2*i, 2*j, ((r * pow(2, 16)) + (g * pow(2, 8)) + b));
			mlx_pixel_put(mlx_ptr, win_ptr, 2*i + 1, 2*j, ((r * pow(2, 16)) + (g * pow(2, 8)) + b));
			mlx_pixel_put(mlx_ptr, win_ptr, 2*i, 2*j + 1, ((r * pow(2, 16)) + (g * pow(2, 8)) + b));
			mlx_pixel_put(mlx_ptr, win_ptr, 2*i + 1, 2*j + 1, ((r * pow(2, 16)) + (g * pow(2, 8)) + b));
			j++;
		}
		i++;
	}
	mlx_string_put(mlx_ptr, win_ptr, 175, 250, (255 * pow(2, 16)) + (255 * pow(2,8)) + 255, "Charles Charlemaine");
	mlx_loop(mlx_ptr);
	return (0);
}
