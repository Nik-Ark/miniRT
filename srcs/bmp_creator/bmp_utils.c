/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:58:26 by lessie            #+#    #+#             */
/*   Updated: 2021/04/27 15:53:10 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_padding(int padding, int fd)
{
	int				i;
	unsigned char	pad;

	pad = (unsigned char)(0);
	i = 0;
	while (i < padding)
	{
		write(fd, &pad, 1);
		i++;
	}
}

void	put_pixel(int color, int fd)
{
	unsigned char	bgr[3];
	int				r;
	int				g;
	int				b;

	r = get_r(color);
	g = get_g(color);
	b = get_b(color);
	bgr[0] = (unsigned char)(b);
	bgr[1] = (unsigned char)(g);
	bgr[2] = (unsigned char)(r);
	write(fd, bgr, 3);
}
