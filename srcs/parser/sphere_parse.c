/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:51:28 by lessie            #+#    #+#             */
/*   Updated: 2021/04/02 14:51:39 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int     sphere_parse(t_scene **scene, const char *line)
{
    int     i;
    float   vector[3];
    float   diam;
    int     rgb;

    i = 2;
    if (!(check_eat_space(&line[i], &i)))
        return (0);
    if (!(parse_vec(&line[i], vector, 1, &i)))
        return (0);
    if (!(check_eat_space(&line[i], &i)))
        return (0);
    if (!(ft_atof(&line[i], &diam, &i)))
        return (0);
    if (!(check_eat_space(&line[i], &i)))
        return (0);
    if (!(parse_rgb(&line[i], &rgb, &i)))
        return (0);
    if (!(check_end_line(&line[i])))
        return (0);
    return (check_append_sphere(scene, vector, diam, rgb));
}

int     check_append_sphere(t_scene **scene, float *vector, float diam, int rgb)
{
    t_vec       *origin;
    t_sphere    *tmp;
    float       radius;

    if (diam <= 0)
        return (0);
    radius = diam / 2.0;
    tmp = (*scene)->sp_lst;
    if (tmp)
        while (tmp->next)
            tmp = tmp->next;
    origin = new_vec(vector[0], vector[1], vector[2]);
    if (tmp)
        tmp->next = new_sphere(origin, radius, rgb);
    else
        (*scene)->sp_lst = new_sphere(origin, radius, rgb);
    return (1);
}