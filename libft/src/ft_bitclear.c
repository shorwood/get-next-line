/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bitclear.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: shorwood <shorwood@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/04 03:44:19 by shorwood     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/11 21:29:00 by shorwood    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_bitclear(uint8_t *ptr, int i)
{
	if (i == 0)
		*ptr &= 0b11111110;
	else if (i == 1)
		*ptr &= 0b11111101;
	else if (i == 2)
		*ptr &= 0b11111011;
	else if (i == 3)
		*ptr &= 0b11110111;
	else if (i == 4)
		*ptr &= 0b11101111;
	else if (i == 5)
		*ptr &= 0b11011111;
	else if (i == 6)
		*ptr &= 0b10111111;
	else if (i == 7)
		*ptr &= 0b01111111;
}
