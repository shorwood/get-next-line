/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 04:41:34 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/26 18:15:27 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.c"

void	test(int fd, int n)
{
	char	*str;
	int		d;

	d = 1;
	str = ft_strnew(0);
	while (n--)
	{
		d = get_next_line(fd, &str);
		ft_putnbr(d);
		ft_putstr(": ");
		ft_putnbr(fd);
		ft_putstr(": ");
		ft_putendl(str);
	}
	ft_putendl("");
}

int		main(void)
{
	
	test(42, 1);

	
	int	fd0;
	int	fd1;
	int	fd2;
	fd0 = open("fsociety.dat00", O_RDONLY);
	fd1 = open("fsociety.dat01", O_RDONLY);
	fd2 = open("fsociety.dat02", O_RDONLY);
	test(fd2, 3);
	test(fd0, 5);
	test(fd1, 4);
	test(fd0, 8);
	test(fd1, 10);
	return (0);
}
