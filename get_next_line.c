/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:24:11 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/09 01:32:30 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

/*
** *****************************************************************************
** Reads 'BUFF_SIZE' bytes from the file descriptor and joins then to the
** corresponding pipe. The new joined string is created using 'strjoin'.
** To avoid memory leaks, the old pipe is freed. The functions returns 1 if
** no errors occured during the reading and string(s) allocations.
** *****************************************************************************
*/

#include <stdio.h>
#include <string.h>

static int	gnl_read(char **pipe, const int fd, ssize_t *len)
{
	char	buf[BUFF_SIZE + 1];
	char	*buf_pipe;
	size_t	len_line;
	size_t	len_read;

	len_line = 0;
	len_read = 0;
	while (*len == BUFF_SIZE && len_line >= len_read)
	{
		*len = read(fd, buf, BUFF_SIZE);
		if (!*len)
			return (0);
		buf[*len] = '\0';
		if (!(buf_pipe = ft_strjoin(*pipe, buf)))
			return (-1);
		free(*pipe);
		*pipe = buf_pipe;
		len_read += *len;
		len_line = ft_strcspn(*pipe, "\n");
	}
	return (0);
}

/*
** *****************************************************************************
** At first, Checks if the pipe is empty or uncomplete by looking for a '\n'
** and comparing the BUFF_SIZE with the last read() call. If the line is valid,
** we set the line, store the overflow in the pipe, free the old pipe
** and return 1. Otherwise we return -1 asap if an error happened.
** *****************************************************************************
*/

static int	gnl_line(char **pipe, char **line, ssize_t *len)
{
	char	*buf;
	char	*nxt;

	if (!*pipe || !**pipe)
		return (0);
	nxt = ft_strchr(*pipe, '\n');
	if (!nxt && *len == BUFF_SIZE)
		return (0);
	if (nxt)
		*nxt = '\0';
	if (!(*line = ft_strdup(*pipe)))
		return (-1);
	buf = NULL;
	if (nxt)
		if (!(buf = ft_strdup(nxt + 1)))
			return (-1);
	free(*pipe);
	*pipe = buf;
	return (1);
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
	static char		*pipes[GNL_FD_MAX] = { NULL };
	char			**pipe;
	int				ret;
	ssize_t			len;

	if (fd < 0 || fd >= GNL_FD_MAX || !line || BUFF_SIZE < 1 ||
		read(fd, NULL, 0) < 0)
		return (-1);
	pipe = &pipes[fd];
	len = BUFF_SIZE;
	if ((ret = gnl_line(pipe, line, &len)))
		return (ret);
	if ((ret = gnl_read(pipe, fd, &len)))
		return (ret);
	return (gnl_line(pipe, line, &len));
}
