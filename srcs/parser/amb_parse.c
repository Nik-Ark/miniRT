/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:47:56 by lessie            #+#    #+#             */
/*   Updated: 2021/04/02 14:48:38 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int     amb_parse(t_scene **scene, const char *line)
{
    int     i;
    float   inten;
    int     rgb;

    i = 1;
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
    return (check_append_amb(scene, inten, rgb));
}

int     check_append_amb(t_scene **scene, float inten, int rgb)
{
    if ((*scene)->amb)
        return (0);
    if (inten < 0.0 || inten > 1.0)
        return (0);
    (*scene)->amb = new_amb(rgb, inten);
    (*scene)->colb = new_colb((*scene)->amb);
    return (1);
}