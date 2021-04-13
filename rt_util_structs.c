/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_util_structs.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:58:18 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/12 12:15:38 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include <stdlib.h>

t_vector	*rt_parse_vector(const char *str)
{
	t_vector	*coords;
	char		**split;

	split = ft_split(str, ',');
	coords = malloc(sizeof(t_vector));
	coords->x = ft_atof(split[0]);
	coords->y = ft_atof(split[1]);
	coords->z = ft_atof(split[2]);
	rt_freesplit(split);
	return (coords);
}

t_rgb	*rt_parse_colour(const char *str)
{
	t_rgb	*color;
	char	**split;

	split = ft_split(str, ',');
	color = malloc(sizeof(t_rgb));
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	rt_freesplit(split);
	return (color);
}

void	rt_parse_resolution(const char **line, void *scene)
{
	t_resolution	*res;

	res = malloc(sizeof(t_resolution));
	if (((t_scene *)scene)->res != NULL || res == NULL)
		return ;
	res->h = ft_atoi(line[1]);
	res->v = ft_atoi(line[2]);
	res->ratio = (double)res->h / (double)res->v;
	((t_scene *)scene)->res = res;
}

void	rt_parse_ambient(const char **line, void *scene)
{
	t_ambient	*a;

	a = malloc(sizeof(t_ambient));
	if (((t_scene *)scene)->amb != NULL || a == NULL)
		return ;
	a->ratio = ft_atof(line[1]);
	a->color = rt_parse_colour(line[2]);
	((t_scene *)scene)->amb = a;
}
