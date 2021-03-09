/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testimage.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 14:09:35 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/09 17:30:21 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_opengl_20191021/mlx.h"
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	void *data_ptr;
}				t_mlx;

int	key_image(int key, void *param)
{
	int colour;
	int i;
	int j;
	t_mlx *tparam;
	
	j = 0;
	tparam = (t_mlx *)param;
	while (j < 255)
	{
		i = 0;
		while (i < 255)
		{
			colour = mlx_get_color_value(tparam->mlx_ptr, i + (j << 16) + (((i * j)%255) << 8));
			((int *)tparam->data_ptr)[i + (255 * j)] = colour;
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(tparam->mlx_ptr, tparam->win_ptr, tparam->img_ptr, 100, 100);
	return (0);
}

int main(void)
{
	t_mlx mlx;
	int size_line, bits_per_pixel, endian;
	
	size_line = 255*255;
	bits_per_pixel = 8 * sizeof(int);
	endian = 1;
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 510, 510, "Charles Charlemaine");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, 255, 255);
	mlx.data_ptr = mlx_get_data_addr(mlx.img_ptr, &bits_per_pixel, &size_line, &endian);
	mlx_key_hook(mlx.win_ptr, key_image, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
