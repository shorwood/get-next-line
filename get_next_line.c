/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:24:11 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/14 05:07:35 by shorwood    ###    #+. /#+    ###.fr     */
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
	int	peak;

	peak = 1;
	if (!gnl)
		return (-1);
	while (!ft_strchr(gnl->buf, '\n') && (gnl->len == BUFF_SIZE || peak--))
		if (!(gnl->buf = ft_strnew(BUFF_SIZE))
			|| (gnl->len = read(gnl->fd, gnl->buf, BUFF_SIZE)) < 0
			|| !ft_lstpush(gnl->pipe, gnl->buf))
			return (-1);
	ft_strsep(&gnl->buf, "\n");
	if ((gnl->buf && !(gnl->buf = ft_strdup(gnl->buf)))
		|| !(*line = ft_lstcat(gnl->pipe)))
		return (-1);
	if (!gnl->len && !ft_strlen(*line) && !ft_strlen(gnl->buf))
	{
		gnl->len = 1;
		ft_lstclr(gnl->pipe, 3);
		ft_strdel(line);
		return (0);
	}
	ft_lstclr(gnl->pipe, 7);
	gnl->pipe = ft_lstnew(1, gnl->buf);
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
	if (!(gnl->pipe = ft_lstnew(0))
		|| !(ft_lstadd(&plst, gnl)))
	{
		free(gnl->pipe);
		free(gnl);
		return (NULL);
	}
	gnl->fd = fd;
	gnl->buf = NULL;
	gnl->len = BUFF_SIZE;
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
	if (!line || read(fd, NULL, 0) < 0)
		return (-1);
	return (gnl_read(gnl_pipe(fd), line));
}
