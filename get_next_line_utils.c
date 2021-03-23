/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mteerlin <mteerlin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 15:06:51 by mteerlin      #+#    #+#                 */
/*   Updated: 2020/11/24 18:00:24 by mteerlin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*gnl_strchr(const char *s, int c)
{
	size_t offset;

	offset = 0;
	while (s[offset] != '\0')
	{
		if (s[offset] == (char)c)
			return ((char *)&s[offset]);
		offset++;
	}
	if (c == '\0')
		return ((char *)&s[offset]);
	return (NULL);
}

void	gnl_strncpy(char *dst, const char *src, size_t n)
{
	size_t offset;
	size_t len;

	if (!src || !dst || n == 0)
		return ;
	offset = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	while (offset < (n - 1) && src[offset] != '\0')
	{
		dst[offset] = src[offset];
		offset++;
	}
	dst[offset] = '\0';
	return ;
}

void	gnl_strncat(char *dst, char *src, size_t n)
{
	size_t offd;
	size_t offs;
	size_t lens;

	offd = 0;
	offs = 0;
	lens = 0;
	while (dst[offd] != '\0')
		offd++;
	while (src[lens] != '\0')
		lens++;
	if (n == 0 || offd >= n)
		return ;
	while (src[offs] != '\0' || offd < (n - 1))
	{
		dst[offd] = src[offs];
		offd++;
		offs++;
	}
	if (offd < n)
		dst[offd] = '\0';
	return ;
}

char	*gnl_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = 1;
	while (s[len - 1] != '\0')
		len++;
	dup = (char *)malloc(len * sizeof(char));
	if (dup == NULL)
		return (NULL);
	gnl_strncpy(dup, s, len);
	return (dup);
}

char	*gnl_strjoin(char *d, char *s)
{
	size_t	len;
	size_t	lend;
	size_t	lens;
	char	*join;

	if (d == NULL || s == NULL)
		return (NULL);
	lend = 0;
	lens = 0;
	while (d[lend] != '\0')
		lend++;
	while (s[lens] != '\0')
		lens++;
	len = lend + lens + 1;
	join = (char *)malloc(len * sizeof(char));
	if (join == NULL)
		return (NULL);
	gnl_strncpy(join, (char *)d, lend + 1);
	gnl_strncat(join, (char *)s, len);
	return (join);
}
