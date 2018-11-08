/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:24:11 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 11:27:22 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

/*
** *****************************************************************************
*/

/*
** Reads 'BUFF_SIZE' bytes from the file descriptor and joins then to the
** corresponding pipe. The new joined string is created using 'strjoin'.
** To avoid memory leaks, the old pipe is freed. The functions returns 1 if
** no errors occured during the reading and string(s) allocations.
*/

#if (BUFF_SIZE > 8000000)

static int	gnl_read(const int fd, char **pipe, ssize_t *len)
{
	char	*buff;
	char	*buf;

	if (!(buff = malloc(BUFF_SIZE + 1)))
		return (0);
	if ((*len = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[*len] = '\0';
		if (!(buf = *pipe ? *pipe : ft_strnew(0)))
			return (0);
		*pipe = ft_strjoin(buf, buff);
		free(buf);
		if (!pipe)
			return (0);
	}
	free(buff);
	return (*len >= 0);
}

#else

static int	gnl_read(const int fd, char **pipe, ssize_t *len)
{
	char	buff[BUFF_SIZE + 1];
	char	*buf;

	if ((*len = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[*len] = '\0';
		if (!(buf = *pipe ? *pipe : ft_strnew(0)))
			return (0);
		*pipe = ft_strjoin(buf, buff);
		free(buf);
		if (!pipe)
			return (0);
	}
	return (*len >= 0);
}

#endif

/*
** At first; Checks for errors in the parameters and exits if there one.
** One of the errors is either the file descriptor being below 0 or above
** the limit of 'FD_MAX' which is the maximum of files that can be opened
** at once by this program. Then checks if so far we have a complete line
** by looking for a newline character. If no newline is found, this function
** returns 0 and exits. If a newline is found, the current line is duplicated
** and set to the 'line' variable. Everything after the newline character is
** duplicated into a new string in 'pipe'. The old pipe is then freed.
*/

static int	gnl_line(char **pipe, char **line)
{
	char	*buf;
	char	*nxt;

	if (!*pipe)
		return (0);
	if (!(nxt = ft_strchr(*pipe, '\n')))
		return (0);
	*nxt = '\0';
	buf = *pipe;
	ft_strdel(line);
	*line = ft_strdup(buf);
	*pipe = ft_strdup(nxt + 1);
	ft_strdel(&buf);
	return (1);
}

/*
** When we don't have anything else to read and there is no newline available
** we enter this function that will handle the last line. We have to make sure
** this line isn't empty otherwise we will count an empty line as a valid line.
** Just as before we duplicate the pipe to the 'line' variable. Then we set the
** first character of the pipe to '\0'. This will help us if 'get_next_line'
** is called once again; So we don't duplicate the last line more than once.
*/

static int	gnl_end(char **pipe, char **line)
{
	if (!*pipe || !**pipe)
		return (0);
	ft_strdel(line);
	*line = ft_strdup(*pipe);
	ft_strdel(pipe);
	return (1);
}

/*
** *****************************************************************************
*/

/*
** The functions first checks for errors and returns -1 if it has
** found one. Then it loops like this: reads the file -> send the lines if it
** has found some. If not it will read the file again. If we have one last line,
** then 'gnl_end' will handle it. This function uses a static string array to
** store read strings into a pipe. Each file descriptor has it's own pipe.
** This part could have been handled with a dynamic array or a linked list
** but ehhh. It is lazy as fuck but it works and avoids memory leaks.
** It only takes 1kb of RAM to accomodate for 1024 possible file descriptors.
*/

int			get_next_line(const int fd, char **line)
{
	static char		*pipe[FD_MAX] = { NULL };
	ssize_t			len;

	if (fd < 0 || fd >= FD_MAX || !line || BUFF_SIZE < 1)
		return (-1);
	*line = NULL;
	while (1)
		if (!gnl_read(fd, &pipe[fd], &len))
			return (-1);
		else if (gnl_line(&pipe[fd], line))
			return (1);
		else if (len < BUFF_SIZE)
			return (gnl_end(&pipe[fd], line));
}
