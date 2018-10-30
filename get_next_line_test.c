/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_test.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 04:41:34 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/30 06:36:41 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

/*
** *****************************************************************************
*/

static void	test(int fd, int n)
{
	char	*str;
	int		d;

	while (n--)
	{
		str = NULL;
		d = get_next_line(fd, &str);
		printf("| %-2d | fd: %-2d| %-22p-\t\t%s\n", d, fd, str, str);
		free(str);
	}
	printf("+\n");
}

/*
** *****************************************************************************
*/

int			main(void)
{
	int fd0;
	int fd1;
	int fd2;

	fd0 = open("get_next_line.c", O_RDONLY);
	fd1 = open("get_next_line.h", O_RDONLY);
	fd2 = open("auteur", O_RDONLY);
	test(fd1, 12);
	test(fd0, 12);
	test(fd1, 9);
	test(fd2, 3);
	close(fd0);
	close(fd1);
	close(fd2);
	test(fd0, 1);
	test(fd1, 1);
	test(fd2, 1);
	return (0);
}
