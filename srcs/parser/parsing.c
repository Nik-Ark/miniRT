/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:48:04 by lessie            #+#    #+#             */
/*   Updated: 2021/03/31 15:49:22 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int     open_fd(const char *filename)
{
    int     fd;
    int     i;

    if ((fd = open(filename, O_RDONLY)) <= 0)
        error_exit(-5);
    i = 0;
    while (filename[i] != '.' && filename[i])
        i++;
    if (!i)
        error_exit(-7);
    if (!(ft_strcmp(&filename[i], ".rt")))
        error_exit(-8);
    return (fd);
}

t_scene     *parsing(int fd)
{
    int     ret;
    t_scene *scene;
    char    *line;

    line = NULL;
    scene = new_scene();
    while ((ret = get_next_line(fd, &line)) > 0)
    {
        if (!(parse_line(&scene, line))) // if leaks try to free scene if error here!
            error_exit(-9);
        free(line);
    }
    if (ret < 0 || !(parse_line(&scene, line))) // if leaks try to free scene if error here!
        error_exit(-9);
    close(fd);
    if (scene->resolution_x == 0 || scene->resolution_y == 0 || scene->cam_lst == NULL) // if leaks try to free scene if error here!
        error_exit(-9);
    if (scene->amb == NULL) // SHOULD I SPIT ERROR IF AMBIENT ABSENT IN DESCRIPTION FILE ??
    {
        scene->amb = new_amb(16777215, 0.0);
        scene->colb = new_colb(scene->amb);
    }
    return (scene);
}

int     parse_line(t_scene **scene, const char *line)
{
    if (line[0] == '\0')
        return (1);
    if (line[0] == '#')
        return (1);
    if (line[0] == 'R')
        return (res_parse(scene, line));
    if (line[0] == 'A')
        return (amb_parse(scene, line));
    if (line[0] == 'c' && line[1] == 'y')
        return (cylinder_parse(scene, line));
    if (line[0] == 'c')
        return (cam_parse(scene, line));
    if (line[0] == 'l')
        return (light_parse(scene, line));
    if (line[0] == 's' && line[1] == 'p')
        return (sphere_parse(scene, line));
    if (line[0] == 'p' && line[1] == 'l')
        return (plane_parse(scene, line));
    if (line[0] == 't' && line[1] == 'r')
        return (triangle_parse(scene, line));
    return (0);
}

int     parse_rgb(const char *line, int *rgb, int *i)
{
    int     j;
    int     r;
    int     g;
    int     b;

    j = 0;
    if (!(ft_atoi(line, &r, &j)))
        return (0);
    if (line[j++] != ',')
        return (0);
    if (!(ft_atoi(&line[j], &g, &j)))
        return (0);
    if (line[j++] != ',')
        return (0);
    if (!(ft_atoi(&line[j], &b, &j)))
        return (0);
    if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
        return (0);
    *rgb = create_rgb(r, g, b);
    *i += j;
    return (1);
}


