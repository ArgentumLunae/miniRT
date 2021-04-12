/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_free_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/02 17:39:27 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/04/09 18:47:05 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtscene.h"

void	rt_freesplit(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	rt_free_ray(t_ray ray)
{
	free(ray.start);
	free(ray.dir);
}
