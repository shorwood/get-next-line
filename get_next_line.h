/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:01:38 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/24 18:45:03 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef _GET_NEXT_LINE_H
# define _GET_NEXT_LINE_H
# define BUFF_SIZE 2
# include "libft.h"

typedef struct	s_gnl
{
	int			fd;
	int			eof;
	t_lst		pipe;
}				t_gnl;

int	get_next_line(const int fd, char **line);
#endif
