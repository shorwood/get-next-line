/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 04:41:34 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/28 19:42:29 by shorwood    ###    #+. /#+    ###.fr     */
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
	free(str);
	ft_putendl("");
}

int		main(void)
{
	
	//test(42, 1);

	
	int	fd0;
	int	fd1;
	int	fd2;
	int	fd3;
	fd0 = open("test00.txt", O_RDONLY);
	fd1 = open("test01.txt", O_RDONLY);
	fd2 = open("test02.txt", O_RDONLY);
	fd3 = open("test03.txt", O_RDONLY);
	test(fd2, 3);
	test(fd0, 5);
	test(fd1, 4);
	test(fd0, 8);
	test(fd1, 10);
	//test(fd3, 1);*/
	return (0);
}
