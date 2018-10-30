/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:24:11 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/30 06:51:03 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "libft/libft.h"
#include "get_next_line.h"

/*
** *****************************************************************************
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
** Reads 'BUFF_SIZE' bytes from the file descriptor and joins then to the
** corresponding pipe. The new joined string is created using 'strjoin'.
** To avoid memory leaks, the old pipe is freed. The functions returns 1 if
** no errors occured during the reading and string(s) allocations.
*/

static int	gnl_read(const int fd, char **pipe, ssize_t *len)
{
	char	*buff;
	char	*buf;

	if (!pipe || !(buff = malloc(BUFF_SIZE + 1)))
		return (0);
	if ((*len = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[*len] = '\0';
		buf = *pipe ? *pipe : ft_strnew(0);
		*pipe = ft_strjoin(buf, buff);
		free(buf);
	}
	free(buff);
	return (*len >= 0);
}

/*
** Checks if so far we have a complete line by looking for a newline
** character. If no newline is found, this function is (kinda) bypassed. If
** a newline is found, the current line is duplicated and set to the 'line'
** variable. Everything after the newline character is duplicated into a new
** string in 'pipe'. The old pipe string is then freed.
*/

static int	gnl_line(char **pipe, char **line)
{
	char	*buf;
	char	*nxt;

	if (!line || !pipe || !*pipe)
		return (0);
	if (!(nxt = ft_strchr(*pipe, '\n')))
		return (0);
	*nxt = '\0';
	buf = *pipe;
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
	if (!line || !pipe || !*pipe || !**pipe)
		return (0);
	*line = ft_strdup(*pipe);
	**pipe = '\0';
	return (1);
}

/*
** *****************************************************************************
*/

/*
** This function use a static string array to store read string into a pipe.
** Each file descriptor has it's own string. This method is lazy as fuck but it
** works and avoids memory leaks. It 'only' takes 82kB of RAM to accomodate
** for all the possible file descriptors. This part could have been handled
** with a dynamic array or a linked list but ehhh. The functions first checks
** for errors and returns -1 if it has found one. Then it loops like this: 
** reads the file -> send the lines if it has found some. If not it will read
** the file again. If we have one last line, then 'gnl_end' will handle it.
*/

int			get_next_line(const int fd, char **line)
{
	static char		*pipe[OPEN_MAX] = {NULL};
	ssize_t			len;

	if (gnl_error(fd, line))
		return (-1);
	while (1)
	{
		if (!gnl_read(fd, pipe + fd, &len))
			return (-1);
		if (gnl_line(pipe + fd, line))
			return (1);
		if (len < BUFF_SIZE)
			return (gnl_end(pipe + fd, line));
	}
}
