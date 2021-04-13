/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_square.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 16:53:29 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/10 13:14:30 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	rt_parse_square(const char **line, void *scene)
{
	t_square	*newsq;

	newsq = malloc(sizeof(t_square));
	newsq->coords = rt_parse_vector(line[1]);
	newsq->o_vect = rt_parse_vector(line[2]);
	newsq->side_size = ft_atof(line[3]);
	newsq->color = rt_parse_colour(line[4]);
	newsq->next = NULL;
	if (((t_scene *)scene)->sq == NULL)
		((t_scene *)scene)->sq = newsq;
	else
	{
		while (((t_scene *)scene)->sq->next != NULL)
			((t_scene *)scene)->sq = ((t_scene *)scene)->sq->next;
		((t_scene *)scene)->sq->next = newsq;
	}
}

void	rt_freesq(t_square *sq)
{
	t_square	*temp;

	while (sq != NULL)
	{
		temp = sq->next;
		free(sq->coords);
		free(sq->o_vect);
		free(sq->color);
		free(sq);
		sq = temp;
	}
}
