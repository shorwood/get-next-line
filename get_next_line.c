/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:24:11 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/09 21:42:50 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "libft.h"
#include "get_next_line.h"

/*
** *****************************************************************************
** Reads 'BUFF_SIZE' bytes from the file descriptor and joins them to the
** corresponding pipe. The new joined string is created using 'strnjoin'.
** To avoid memory leaks, the old pipe is freed. The functions returns 1 if
** no errors occured during the reading and string(s) allocations.
** *****************************************************************************
*/

static int		gnl_read(t_gnl *gnl, char **line)
{
	char	*buf;
	int		peak;

	peak = 1;
	if (!gnl || !gnl->len)
		return (!gnl ? -1 : 0);
	buf = gnl->pipe[0] ? (char*)gnl->pipe[0]->data : NULL;
	while (!ft_strchr(buf, '\n') && (gnl->len == BUFF_SIZE || peak--))
		if (!(buf = ft_strnew(BUFF_SIZE))
			|| (gnl->len = read(gnl->fd, buf, BUFF_SIZE)) < 0
			|| !ft_lstpush(gnl->pipe, buf))
			return (-1);
	ft_strsep(&buf, "\n");
	if (!(*line = ft_lstcat(gnl->pipe)))
		return (-1);
	if (gnl->len <= 0 && !ft_strlen(*line) && !ft_strlen(buf))
	{
		ft_lstclr(gnl->pipe, 1);
		ft_strdel(line);
		return (0);
	}
	buf = ft_strdup(buf);
	ft_lstclr(gnl->pipe, 1);
	gnl->pipe = ft_lstnew(1, buf);
	return (1);
}

/*
** *****************************************************************************
** Search a specific file descriptor from the static list of 'GNL handlers'.
** If not found, will create and initialize one for us. Each 'GNL handlers'
** contains the file decriptor value, a list of strings, and an EOF flag.
** *****************************************************************************
*/

static t_gnl	*gnl_pipe(int fd)
{
	static t_lsti	plst = NULL;
	t_gnl			*gnl;
	t_lsti			cur;

	cur = plst;
	while (cur)
	{
		if (((t_gnl*)cur->data)->fd == fd)
			return (cur->data);
		cur = cur->next;
	}
	if (!(gnl = (t_gnl*)malloc(sizeof(t_gnl))))
		return (NULL);
	gnl->fd = fd;
	gnl->len = BUFF_SIZE;
	gnl->pipe = ft_lstnew(0);
	ft_lstadd(&plst, gnl);
	return (gnl);
}

/*
** *****************************************************************************
** The functions first checks for errors and returns -1 if it has found one.
** Then it will check, return and set the line if one is available in the pipe.
** If not, the function then reads from the file descriptor and joins the read
** bytes into the pipe until it has reached the end of file or a newline.
** now that we are sure we have a complete line, we return and set the line.
** *****************************************************************************
** This function uses a static string array to store read strings into a pipe.
** Each file descriptor has it's own pipe. This part could have been handled
** with a dynamic array or a linked list but ehhh. It is lazy as fuck but it
** works and avoids memory leaks. It only takes 1kb of RAM to accomodate for
** 1024 possible file descriptors.
** *****************************************************************************
*/

int				get_next_line(const int fd, char **line)
{
	if (!line || fd == -1)
		return (-1);
	*line = NULL;
	if (read(fd, NULL, 0) < 0)
		return (-1);
	return (gnl_read(gnl_pipe(fd), line));
}
