/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:24:11 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/26 19:23:23 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"

static t_gnl	*gnl_find(t_gnl **gnl, int fd)
{
	t_gnl	*buf;

	if (!gnl)
		return (NULL);
	buf = *gnl;
	while (buf)
	{
		if (buf->fd == fd)
			return (buf);
		buf = buf->next;
	}
	return (NULL);
}

static t_gnl	*gnl_insert(t_gnl **gnl, int fd)
{
	t_gnl	*new;

	if (!gnl || !(new = (t_gnl*)ft_malloc(sizeof(t_gnl))))
		return (NULL);
	new->fd = fd;
	new->pipe = ft_calloc(1, sizeof(char));
	new->next = *gnl;
	new->read = BUFF_SIZE;
	return ((*gnl = new));
}
/*
**	Checks:
**	- 'fd' File descriptor is valid and above 0.
**	- 'line' pointer is not NULL.
**	- 'cur->pipe' pointer is not NULL (meaning the gnl_find && gnl_insert worked).
**	- 'cur->read' is above 0 meaning we had no read errors.
**	- 'BUFF_SIZE' macro is above 0 because we wont go far with no memory.
*/
int				get_next_line(const int fd, char **line)
{
	static t_gnl	*gnl;
	t_gnl			*cur;
	char			*pipe;
	char			*buf;

	if (!(cur = gnl_find(&gnl, fd)))
		if (!(cur = gnl_insert(&gnl, fd)))
			return (-1);
	if (fd < 0 || !line || !cur->pipe || cur->read < 0 || BUFF_SIZE <= 0)
		return (-1);
	pipe = cur->pipe;
	if (cur->read == 0)
	{
		*line = cur->pipe;
		return (0);
	}
	if ((buf = ft_strchr(pipe, '\n')))
	{
		*buf = '\0';
		*line = ft_strdup(cur->pipe);
		cur->pipe = ft_strdup(buf + 1);
		return (1);
	}
	if (cur->read < BUFF_SIZE)
	{
		if (*pipe)
			*line = ft_strdup(pipe);
		return (!!*pipe);
	}
	buf = ft_calloc(BUFF_SIZE + 2, sizeof(char));
	if ((cur->read = read(fd, buf, BUFF_SIZE)) >= 0)
		cur->pipe = ft_strjoin(pipe, buf);
	free(pipe);
	free(buf);
	return (get_next_line(fd, line));
}
