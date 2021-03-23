/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 16:20:17 by mteerlin      #+#    #+#                 */
/*   Updated: 2020/11/28 19:00:13 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int		get_next_line(int fd, char **line);
char	*gnl_strchr(const char *s, int c);
void	gnl_strncpy(char *dst, const char *src, size_t n);
void	gnl_strncat(char *dst, char *src, size_t n);
char	*gnl_strdup(const char *s);
char	*gnl_strjoin(char *d, char *s);

#endif
