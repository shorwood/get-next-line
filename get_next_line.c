/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:24:11 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 17:33:28 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

/*
** *****************************************************************************
** Reads and push the file string into a list. All the strings in the list
** are then assembled into a single string. Trailing characters after the first
** newline character are cut and saved for later. If the end of file is
** detected, we exit and return 0 ; else 1.
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
** Each time it is called, the function will try to find if the input file
** descriptor has already been processed. It will then either retreive the
** corresponding 'GNL handlers' object or create it if not found. This object is
** then send to the 'gnl_read' function that will read from the file descriptor
** and take care of the overflow. Any error during the function will abort it
** and send a '-1' error code.
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
