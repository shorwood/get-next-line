/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 04:41:34 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/30 01:13:30 by shorwood    ###    #+. /#+    ###.fr     */
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

	str = NULL;
	while (n--)
	{
		d = get_next_line(fd, &str);
		ft_putnbr(d);
		ft_putstr(": ");
		ft_putnbr(fd);
		ft_putstr(": ");
		ft_putendl(str);
		ft_strdel(&str);
	}
	ft_putendl("");
}

int		main(void)
{
	int fd0;
	int fd1;
	int fd2;
	//int fd3;

	fd0 = open("test00.txt", O_RDONLY);
	test(fd0, 11);
	close(fd0);
	test(fd0, 1);
	fd1 = open("test01.txt", O_RDONLY);
	test(fd1, 4);
	test(fd1, 10);
	close(fd1);
	test(fd1, 1);
	fd2 = open("test02.txt", O_RDONLY);
	test(fd2, 3);
	close(fd2);
	/*test(fd2, 1);
	fd3 = open("test03.txt", O_RDONLY);
	test(fd3, 10);*/
	return (0);
}
