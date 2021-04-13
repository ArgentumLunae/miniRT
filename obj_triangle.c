/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_triangle.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:54:07 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/10 13:13:56 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	rt_parse_triangle(const char **line, void *scene)
{
	t_triangle	*newtr;

	newtr = malloc(sizeof(t_triangle));
	if (newtr == NULL)
		return ;
	newtr->coord1 = rt_parse_vector(line[1]);
	newtr->coord2 = rt_parse_vector(line[2]);
	newtr->coord3 = rt_parse_vector(line[3]);
	newtr->color = rt_parse_colour(line[4]);
	newtr->next = NULL;
	if (((t_scene *)scene)->tr == NULL)
		((t_scene *)scene)->tr = newtr;
	else
	{
		while (((t_scene *)scene)->tr->next != NULL)
			((t_scene *)scene)->tr = ((t_scene *)scene)->tr->next;
		((t_scene *)scene)->tr->next = newtr;
	}
}

void	rt_freetr(t_triangle *tr)
{
	t_triangle	*temp;

	while (tr != NULL)
	{
		temp = tr->next;
		free(tr->coord1);
		free(tr->coord2);
		free(tr->coord3);
		free(tr->color);
		free(tr);
		tr = temp;
	}
}
