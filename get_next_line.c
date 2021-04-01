/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 11:48:19 by mteerlin      #+#    #+#                 */
/*   Updated: 2021/03/25 12:54:40 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "get_next_line.h"

int		read_next_line(int fd, int ret, char *buff, char **str)
{
	char *temp;

	ret = read(fd, buff, BUFFER_SIZE);
	while (ret > 0)
	{
		buff[ret] = '\0';
		if (*str == NULL)
		{
			*str = gnl_strdup(buff);
			if (*str == NULL)
				return (-1);
		}
		else
		{
			temp = gnl_strjoin(*str, buff);
			free(*str);
			*str = temp;
			if (*str == NULL)
				return (-1);
		}
		if (gnl_strchr(*str, '\n') != NULL)
			break ;
		ret = read(fd, buff, BUFFER_SIZE);
	}
	return (ret);
}

void	trim_line(char **str, char **line)
{
	int		len;
	char	*temp;

	len = 0;
	while ((*str)[len] != '\n' && (*str)[len] != '\0')
		len++;
	if ((*str)[len] == '\n')
	{
		(*str)[len] = '\0';
		*line = gnl_strdup(*str);
		temp = gnl_strdup(&(*str)[len + 1]);
		free(*str);
		*str = temp;
	}
	else
	{
		*line = gnl_strdup(*str);
		free(*str);
		*str = NULL;
	}
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	static char *str[1024];
	char		buff[BUFFER_SIZE + 1];

	if (BUFFER_SIZE == 0 || fd < 0 || line == NULL)
		return (-1);
	if (str[fd] != NULL && gnl_strchr(str[fd], '\n'))
		ret = 0;
	else
		ret = read_next_line(fd, 1, buff, &str[fd]);
	if (ret < 0)
	{
		*line = gnl_strdup("");
		return (-1);
	}
	if (ret == 0 && str[fd] == NULL)
	{
		*line = gnl_strdup("");
		return (0);
	}
	trim_line(&str[fd], line);
	if (ret < BUFFER_SIZE && str[fd] == NULL)
		return (0);
	return (1);
}
