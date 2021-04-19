/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:59:38 by lessie            #+#    #+#             */
/*   Updated: 2021/04/14 17:59:50 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    create_bmp(t_scene *scene, const char *filename_rt)                         // !!! TRY Static Void     ????
{
    char            *filename;
    int             fd;
    int             res_x;
    int             res_y;
    int             padding;
    int             num_of_bytes;

    res_x = (int)(scene->resolution_x);
    res_y = (int)(scene->resolution_y);
    padding = (4 - ((res_x * 3) % 4)) % 4;
    num_of_bytes = (res_x * res_y * 3) + (padding * res_y) + 54;


    filename = get_filename(filename_rt);
    if ((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0655)) <= 0)   // !!! TRY 0655 TOO... OR 0644
        error_exit(10);
    write_first_header(num_of_bytes, fd);
    write_second_header(res_x, res_y, fd);

    write_pixels(scene, padding, fd);

    close(fd);
}

char    *get_filename(const char *filename_rt)
{
    char    *filename;
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (filename_rt[i] != '.')
        i++;
    if (!(filename = malloc(sizeof(char) * (5 + i))))
        error_exit(-2);
    while (j <= i)
    {
        filename[j] = filename_rt[j];
        j++;
    }
    filename[j++] = 'b';
    filename[j++] = 'm';
    filename[j++] = 'p';
    filename[j] = '\0';
    return (filename);
}

void    write_first_header(int num_of_bytes, int fd)
{
    unsigned char   header[14];
    int             i;

    i = 0;
    while (i < 14)
        header[i++] = (unsigned char)(0);
    header[0] = (unsigned char)('B');
    header[1] = (unsigned char)('M');
    header[2] = (unsigned char)(num_of_bytes);
    header[3] = (unsigned char)(num_of_bytes >> 8);
    header[4] = (unsigned char)(num_of_bytes >> 16);
    header[5] = (unsigned char)(num_of_bytes >> 24);
    header[10] = (unsigned char)(54);
    write(fd, header, 14);
}

void    write_second_header(int res_x, int res_y, int fd)
{
    unsigned char   header[40];
    int             i;

    i = 0;
    while (i < 40)
        header[i++] = (unsigned char)(0);
    header[0] = (unsigned char)(40);
    header[4] = (unsigned char)(res_x);
    header[5] = (unsigned char)(res_x >> 8);
    header[6] = (unsigned char)(res_x >> 16);
    header[7] = (unsigned char)(res_x >> 24);
    header[8] = (unsigned char)(res_y);
    header[9] = (unsigned char)(res_y >> 8);
    header[10] = (unsigned char)(res_y >> 16);
    header[11] = (unsigned char)(res_y >> 24);
    header[12] = (unsigned char)(1);
    header[14] = (unsigned char)(24);
    write(fd, header, 40);
}

void    write_pixels(t_scene *scene, int padding, int fd)
{
    int         color;
    t_vplane	*vplane;        // MOVE IT INTO SCENE
    t_closest	*closest;       // MOVE IT INTO SCENE
    float		y;
    float		x;

    vplane = get_vplane(scene->resolution_x, scene->resolution_y, scene->cam_lst->fov);       // MOVE IT INTO SCENE
    closest = new_closest();                                                                 // MOVE IT INTO SCENE
    y = 0;
    while (y < scene->resolution_y)
    {
        x = 0;
        while (x < scene->resolution_x)
        {
            canvas_to_vplane(y, x, closest, vplane);
            color = all_intersects(closest, scene);
            put_pixel(color, fd);
            x++;
            if (x == scene->resolution_x && padding)
                add_padding(padding, fd);
        }
        y++;
    }
    free(vplane);        // MOVE IT INTO FREE_SCENE
    free(closest);       // MOVE IT INTO FREE_SCENE
}

void    put_pixel(int color, int fd)
{
    unsigned char   bgr[3];
    int             r;
    int             g;
    int             b;

    r = get_r(color);
    g = get_g(color);
    b = get_b(color);
    bgr[0] = (unsigned char)(b);
    bgr[1] = (unsigned char)(g);
    bgr[2] = (unsigned char)(r);
    write(fd, bgr, 3);
}

























