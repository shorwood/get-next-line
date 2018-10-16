/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_test.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 04:41:34 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 05:33:18 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "get_next_line.c"
#include "LibFt/libft.h"

int		main(void)
{
	char	*str;
	int		fd;

	fd = fopen("fsociety.dat00", "r");
	get_next_line(fd, &str);
	ft_putstr(str);
	return 0;
}
