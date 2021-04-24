/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:58:26 by lessie            #+#    #+#             */
/*   Updated: 2021/04/15 17:58:48 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned char   *ft_bmp_alloc(int bytes)
{
    unsigned char   *addr;
    unsigned char   *zero;
    int             i;

    i = 0;
    if (!(addr = malloc(sizeof(unsigned char) * bytes)))
        error_exit(-2);
    zero = addr;
    while (i < bytes)
    {
        zero[i] = (unsigned char)0;
        i++;
    }
    return (addr);
}

void    add_padding(int padding, int fd)
{
    int     i;
    unsigned char   pad;

    pad = (unsigned char)(0);
    i = 0;
    while (i < padding)
    {
        write(fd, &pad, 1);
        i++;
    }
}