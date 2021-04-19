/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:50:46 by lessie            #+#    #+#             */
/*   Updated: 2021/04/02 14:50:56 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int     light_parse(t_scene **scene, const char *line)
{
    int     i;
    float   vector[3];
    float   inten;
    int     rgb;

    i = 1;
    if (!(check_eat_space(&line[i], &i)))
        return (0);
    if (!(parse_vec(&line[i], vector, 1, &i)))
        return (0);
    if (!(check_eat_space(&line[i], &i)))
        return (0);
    if (!(ft_atof(&line[i], &inten, &i)))
        return (0);
    if (!(check_eat_space(&line[i], &i)))
        return (0);
    if (!(parse_rgb(&line[i], &rgb, &i)))
        return (0);
    if (!(check_end_line(&line[i])))
        return (0);
    return (check_append_light(scene, vector, inten, rgb));
}

int     check_append_light(t_scene **scene, float *vector, float inten, int rgb)
{
    t_light *tmp;
    t_vec   *origin;

    if (inten < 0.0 || inten > 1.0)
        return (0);
    origin = new_vec(vector[0], vector[1], vector[2]);
    tmp = (*scene)->light_lst;
    if (tmp)
        while (tmp->next)
            tmp = tmp->next;
    if (tmp)
        tmp->next = new_light(rgb, inten, origin);
    else
        (*scene)->light_lst = new_light(rgb, inten, origin);
    return (1);
}