/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:24:11 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 07:40:41 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#define BUF_SIZE 10000000

#include <unistd.h>
#include "LibFt/libft.h"



int		get_next_line(const int fd, char **line)
{
	char		*buf;
	static char	*str;
	ssize_t		red;

	if (!(str = str ? str : ft_strnew(2 * BUF_SIZE)))
		return (-1);
	if (!(buf = ft_strchr(str, '\n')))
	{
		buf = ft_strnew(BUF_SIZE);
		red = read(fd, buf, BUF_SIZE);
			str = ft_strncat(str, buf, red);
		if (red > 0)
			get_next_line(fd, line);
		return (red > 0);
	}
	*buf = '\0';
	*line = ft_strdup(str);
	buf = ft_strdup(buf + 1);
	free(str);
	str = buf;
	return (1);
}
