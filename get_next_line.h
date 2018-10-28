/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/16 05:01:38 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/28 19:26:00 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef _GET_NEXT_LINE_H
# define _GET_NEXT_LINE_H

# include <unistd.h>
# include "libft.h"
# define BUFF_SIZE 1000

int					get_next_line(const int fd, char **line);



typedef struct		s_gnl
{
	int				fd;
	char			*pipe;
	ssize_t			read;
	struct s_gnl	*next;
}					t_gnl;

#endif
