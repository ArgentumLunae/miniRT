/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testimage.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 14:09:35 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/16 17:21:04 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include "libft.h"
#include <stdlib.h>

typedef struct	s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	void *data_ptr;
}				t_mlx;

int	key_print(int key, void *param)
{
	t_mlx *tparam;

	tparam = (t_mlx *)param;
	ft_putstr_fd("keycode: ", 1);
	ft_putnbr_fd(key, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

int add_shade(double distance, int colour)
{
	int r, g, b;
	b = (1 - distance) * (colour % 256);
	g = (1 - distance) * ((colour >> 8) % 256);
	r = (1 - distance) * ((colour >> 16) % 256);
	return ((r << 16) + (g << 8) + b);
}

int get_opposite(int colour)
{
	int r, g, b;
	
	b = 255 - (colour % 256);
	g = 255 - (((colour >> 8) % 256));
	r = 255 - (((colour >> 16) % 256));
	return ((r << 16) + (g << 8) + b);
}

int	key_circle(int key, void *param)
{
	int coord[2];
	int rad;
	int colour;
	int i, j;
	t_mlx *tparam;

	coord[0] = 255;
	coord[1] = 255;
	rad = key;
	i = 0;
	tparam = (t_mlx *)param;
	while (i < 510)
	{
		j = 0;
		while(j < 510)
		{
			colour = mlx_get_color_value(tparam->mlx_ptr, ((((i * j)) % 256) << 16) + ((j) << 8) + i);
			if (key == 51)
				colour = get_opposite(colour);
			if ((pow((i - coord[0]), 2) + pow((j - coord[1]), 2)) < pow(rad, 2))
			{
				colour = mlx_get_color_value(tparam->mlx_ptr, (255 << 16));
				colour = add_shade((pow((i - coord[0] + 0.1 * rad), 2) + pow((j - coord[1] + 0.1 * rad), 2)) / ( 1.35 * pow(rad, 2)), colour);
			}
			((int *)tparam->data_ptr)[i + (510 * j)] = colour;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(tparam->mlx_ptr, tparam->win_ptr, tparam->img_ptr, 0, 0);
	return (key);
}

int	key_square(int key, void *param)
{
	int coord[2];
	int side;
	int colour;
	int i, j;
	t_mlx *tparam;

	coord[0] = 255;
	coord[1] = 255;
	side = key;
	i = 0;
	tparam = (t_mlx *)param;
	while (i < 510)
	{
		j = 0;
		while(j < 510)
		{
			colour = mlx_get_color_value(tparam->mlx_ptr, ((((i * j)) % 256) << 16) + ((j) << 8) + i);
			if (key == 51)
				colour = get_opposite(colour);
			if (i > (coord[0] - side/2) && i < (coord[0] + side/2) && j > (coord[1] - side/2) && j < (coord[1] + side/2))
			{
				colour = mlx_get_color_value(tparam->mlx_ptr, (255 << 16));
				colour = add_shade((pow((i - coord[0] + 0.1 * side), 2) + pow((j - coord[1] + 0.1 * side), 2)) / ( 1.35 * pow(side, 2)), colour);
			}
			((int *)tparam->data_ptr)[i + (510 * j)] = colour;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(tparam->mlx_ptr, tparam->win_ptr, tparam->img_ptr, 0, 0);
	return (key);
}

int	key_triangle(int key, void *param)
{
	int coord1[2];
	int coord2[2];
	int coord3[2];
	int diff1[2];
	int diff2[2];
	int	diff3[3];
	int side;
	int colour;
	int i, j;
	t_mlx *tparam;

	coord1[0] = 256;
	coord1[1] = 128;
	coord2[0] = 128;
	coord2[1] = 256;
	coord3[0] = 256;
	coord3[1] = 256;
	diff1[0] = coord1[0] - coord2[0];
	diff1[1] = coord1[1] - coord2[1];
	diff2[0] = coord1[0] - coord3[0];
	diff2[1] = coord1[1] - coord3[1];
	diff3[0] = coord2[0] - coord3[0];
	diff3[1] = coord2[1] - coord3[1];
	side = key;
	i = 0;
	tparam = (t_mlx *)param;
	while (i < 510)
	{
		j = 0;
		while(j < 510)
		{
			colour = mlx_get_color_value(tparam->mlx_ptr, ((((i * j)) % 256) << 16) + ((j) << 8) + i);
			if (key == 51)
				colour = get_opposite(colour);
			if (i >= coord1[1] && i <= coord2[1])
				colour = mlx_get_color_value(tparam->mlx_ptr, (255 << 16));
			((int *)tparam->data_ptr)[i + (510 * j)] = colour;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(tparam->mlx_ptr, tparam->win_ptr, tparam->img_ptr, 0, 0);
	return (key);
}

int	mouse_circle(int button, int x, int y, void *param)
{
	int colour;
	int i;
	int j;
	int rad;
	t_mlx *tparam;
	
	j = 0;
	rad = 40 * button;
	tparam = (t_mlx *)param;
	while (j < 510)
	{
		i = 0;
		while (i < 510)
		{
//			colour = mlx_get_color_value(tparam->mlx_ptr, ((((i * j)) % 256) << 16) + ((j) << 8) + i);
			if (sqrt(pow((i - x), 2) + pow((j - y), 2)) <= rad)
			{
				colour = mlx_get_color_value(tparam->mlx_ptr, (255 << 16));
				colour = add_shade((pow((i - x + 0.1 * rad), 2) + pow((j - y + 0.1 * rad), 2)) / ( 1.35 * pow(rad, 2)), colour);
				((int *)tparam->data_ptr)[i + (510 * j)] = colour;
			}
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(tparam->mlx_ptr, tparam->win_ptr, tparam->img_ptr, 0, 0);
	return (button);
}

int main(void)
{
	t_mlx mlx;
	int size_line, bits_per_pixel, endian;
	
	size_line = 510*510;
	bits_per_pixel = 8 * sizeof(int);
	endian = 1;
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 510, 510, "Charles Charlemaine");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, 510, 510);
	mlx.data_ptr = mlx_get_data_addr(mlx.img_ptr, &bits_per_pixel, &size_line, &endian);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, key_triangle, &mlx);
	mlx_hook(mlx.win_ptr, 5, 1L << 2, mouse_circle, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
