/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:24:11 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/28 19:44:35 by shorwood    ###    #+. /#+    ###.fr     */
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
int				get_next_line(const int fd, char **line)
{
	static t_gnl	*gnl;
	t_gnl			*cur;
	char			*pipe;
	char			*buf;
	char			*nxt;


	if (!(cur = gnl_find(&gnl, fd)))
		if (!(cur = gnl_insert(&gnl, fd)))
			return (-1);


	/*
	**	Checks:
	**	- 'fd' File descriptor is valid and above 0.
	**	- 'line' pointer is not NULL.
	**	- 'cur->pipe' pointer is not NULL (meaning the gnl_find && gnl_insert worked).
	**	- 'cur->read' is above 0 meaning we had no read errors.
	**	- 'BUFF_SIZE' macro is above 0 because we wont go far with no memory.
	*/
	if (fd < 0 || !line || !cur->pipe || cur->read < 0 || BUFF_SIZE <= 0)
		return (-1);


	pipe = cur->pipe;
	
	if ((nxt = ft_strchr(cur->pipe, '\n')))
	{
		*nxt = '\0';
		*line = ft_strdup(cur->pipe);
		free(cur->pipe);
		cur->pipe = ft_strdup(nxt + 1);
		return (1);
	}

	int a = 0;
	if (cur->read < BUFF_SIZE)
	{
		if (*cur->pipe)
			*line = cur->pipe;
		cur->read = 0;
		a = cur->read;
		return (*cur->pipe && a);
	}


	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (-1);


	if ((cur->read = read(fd, buf, BUFF_SIZE)) > 0)
		cur->pipe = ft_strjoin(pipe, buf);
	free(buf);
	free(pipe);
	return (get_next_line(fd, line));
}
