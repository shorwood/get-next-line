/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:24:11 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/24 18:43:43 by shorwood    ###    #+. /#+    ###.fr     */
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

static int	gnl_read(t_gnl *fd, char **line)
{
	ssize_t	len;
	ssize_t	n;
	char	*buf;
	
	len = BUFF_SIZE;
	if (!fd)
		return (-1);
	if (fd->eof)
		return (0);


	buf = fd->pipe[0] ? (char*)fd->pipe[0]->data : NULL;


	while (!ft_strchr(buf, '\n') && len == BUFF_SIZE)
		if (!(buf = ft_strnew(BUFF_SIZE)))
			return (-1);
		else if ((len = read(fd->fd, buf, BUFF_SIZE)) < 0)
			return (-1);
		else if (!ft_lstpush(fd->pipe, buf))
			return (-1);


	buf[(n = ft_strcspn(buf, "\n"))] = '\0';
	if (!(*line = ft_lstcat(fd->pipe)))
		return (-1);
	if (!(buf = ft_strdup(buf + n + 1)))
		return (-1);


	ft_lstclr(fd->pipe, 1);
	fd->pipe = ft_lstnew(1, buf);
	fd->eof = len < BUFF_SIZE && !ft_strlen(buf);


	return (1);
}

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
	gnl->eof = 0;
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

int			get_next_line(const int fd, char **line)
{
	if (!line || fd == -1)
		return (-1);
	*line = NULL;
	if (read(fd, NULL, 0) < 0)
		return (-1);
	return (gnl_read(gnl_pipe(fd), line));
}
