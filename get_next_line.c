/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:24:11 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 06:01:15 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>

#include <unistd.h>
#include "LibFt/libft.h"

int		get_next_line(const int fd, char **line)
{
	char		*str;
	char		*buf;
	char		*nxt;
	static char *ovf;
	ssize_t		red;

	str = ovf ? ovf : ft_strnew(64UL);
	buf = ft_strnew(64UL);
	while ((red = read(fd, buf, 64)) > 0L)
	{
		ft_strncat(str, buf, red);
		nxt = ft_strchr(str, '\n');
		if (nxt)
		{
			*nxt = '\0';
			*line = ft_strdup(str);
			ovf = ft_strndup(++nxt, red);
			return (1);
		}
	}
	return (0);
}