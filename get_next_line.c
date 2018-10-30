/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:24:11 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/30 03:41:16 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"
#include "get_next_line.h"

/*
** ****************************************************************************
*/

/*
** Checks for errors in the parameters and returns true if there one.
** One of the errors is either the file descriptor being below 0 or above
** the limit of 'OPEN_MAX' which is the maximum of files that can be opened
** at once by one program. This macro can be found in <limits.h>
*/

static int	gnl_error(const int fd, char **line)
{
	return (fd < 0 || fd > OPEN_MAX || !line || BUFF_SIZE < 1);
}

/*
** Read 'BUFF_SIZE' bytes from the file descriptor and joins
*/

static int	gnl_read(const int fd, char **arr, ssize_t *len)
{
	char	buf[BUFF_SIZE + 1];
	char	*pipe;

	if ((*len = read(fd, buf, BUFF_SIZE)) < 0)
	{
		ft_strdel(&arr[fd]);
		return (0);
	}
	buf[*len] = '\0';
	pipe = arr[fd] ? arr[fd] : ft_strnew(0);
	arr[fd] = ft_strjoin(pipe, buf);
	ft_free(pipe);
	return (1);
}

static int	gnl_line(const int fd, char **arr, char **line)
{
	char	*pipe;
	char	*next;

	if (!arr[fd] || !(next = ft_strchr(arr[fd], '\n')))
	{
		return (0);
	}
	*next = '\0';
	pipe = arr[fd];
	*line = ft_strdup(pipe);
	arr[fd] = ft_strdup(next + 1);
	ft_strdel(&pipe);
	return (1);
}

static int	gnl_end(const int fd, char **arr, char **line)
{
	if (!arr[fd] || !*arr[fd])
		return (0);
	*line = ft_strdup(arr[fd]);
	*arr[fd] = '\0';
	return (1);
}

/*
** ****************************************************************************
*/

int			get_next_line(const int fd, char **line)
{
	static char		*arr[OPEN_MAX] = {NULL};
	ssize_t			len;

	if (gnl_error(fd, line))
		return (-1);
	while (1)
		if (!gnl_read(fd, arr, &len))
			return (-1);
		else if (gnl_line(fd, arr, line))
			return (1);
		else if (len < BUFF_SIZE)
			return (gnl_end(fd, arr, line));
}
