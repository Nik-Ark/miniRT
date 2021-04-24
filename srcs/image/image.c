/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 16:15:04 by lessie            #+#    #+#             */
/*   Updated: 2021/04/24 16:15:23 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    *create_image(void *mlx, t_scene *scene)
{
    int     size_line;
    int     bits_pix;
    int     endian;
    void    *img;
    int     *addr;

    size_line = scene->resolution_x * 4;
    bits_pix = 32;
    endian = 1;
    img = mlx_new_image(mlx, (int)scene->resolution_x, (int)scene->resolution_y);
    addr = (int *)mlx_get_data_addr(img, &bits_pix, &size_line, &endian);
    ray_tracing(addr, scene);
    return (img);
}