/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:24:11 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/30 01:14:15 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	static char		*arr[OPEN_MAX] = {NULL};
	char			buf[BUFF_SIZE + 1];
	char			*next;
	char			*pipe;
	ssize_t			cnt;

	if (fd < 0 || fd > OPEN_MAX || !line || BUFF_SIZE <= 0)
		return (-1);
	while (1)
	{

		if ((cnt = read(fd, buf, BUFF_SIZE)) > 0)
		{
			pipe = arr[fd] ? arr[fd] : ft_strnew(0);
			buf[cnt] = '\0';
			arr[fd] = ft_strjoin(pipe, buf);
			ft_strdel(&pipe);
		}

		else if (cnt < 0)
		{
			ft_strdel(&arr[fd]);
			return (-1);
		}

		if (arr[fd] && (next = ft_strchr(arr[fd], '\n')))
		{
			*next = '\0';
			pipe = arr[fd];
			*line = ft_strdup(pipe);
			arr[fd] = ft_strdup(next + 1);
			ft_strdel(&pipe);
			return (1);
		}
		
		else if (cnt < BUFF_SIZE)
		{
			if (arr[fd] && *arr[fd])
			{
				*line = ft_strdup(arr[fd]);
				*arr[fd] = '\0';
				return (1);
			}
			return (0);
		}
	}
}
