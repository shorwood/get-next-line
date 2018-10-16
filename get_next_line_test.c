/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_test.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 04:41:34 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 07:35:54 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>

#include <fcntl.h>
#include "get_next_line.c"
#include "LibFt/libft.h"

int		main(void)
{
	char	*str;
	int		fd;
	int		d;

	fd = open("fsociety.dat00", O_RDONLY);
	for (int i = 0; i < 10; i++)
	{
		d = get_next_line(fd, &str);
		ft_putnbr(d);
		ft_putendl(str);
	}
	return (0);
}
