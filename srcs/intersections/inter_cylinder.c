/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:23:08 by lessie            #+#    #+#             */
/*   Updated: 2021/04/08 15:23:33 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	inter_cylinder(t_vec *orig, t_vec *dir, t_cyl *cyl)
{
    float   coeff[3];
    float   dist[2];
    float   result;
    
    get_coeff(orig, dir, cyl, coeff);
    if (!(cyl_equation(coeff, dist)))
        return (0);
    if (!(result = trim_cyl(orig, dir, cyl, dist)))
        return (0);
    if (result > 0)
        return (result);
    return (0);
}

void    get_coeff(t_vec *orig, t_vec *dir, t_cyl *cyl, float *coeff)
{
    t_vec   *cyl_o;
    t_vec   *turn_cyl;
    t_vec   *turn_p;
    t_vec   *p_orient;
    t_vec   *p_cyl;

    cyl_o = vec_multipl_on(cyl->orient, dot_product(cyl->orient, dir));
    turn_cyl = vec_subtract(orig, cyl->bottom_p);
    turn_p = vec_multipl_on(cyl->orient, dot_product(cyl->orient, turn_cyl));
    p_orient= vec_subtract(dir, cyl_o);
    p_cyl = vec_subtract(turn_cyl, turn_p);
    coeff[0] = dot_product(p_orient, p_orient);
    coeff[1] = 2.0 * dot_product(p_orient, p_cyl);
    coeff[2] = dot_product(p_cyl, p_cyl) - pow(cyl->radius, 2);
    free(cyl_o);
    free(turn_cyl);
    free(turn_p);
    free(p_orient);
    free(p_cyl);
}

int     cyl_equation(float *coeff, float *dist)
{
    float   discr;
    float   root;

    discr = (coeff[1] * coeff[1]) - (4 * coeff[0] * coeff[2]);
    root = 0;
    if (discr < 0)
        return (0);
    if (discr == 0)
    {
        dist[0] = -0.5 * (coeff[1] / coeff[0]);
        dist[1] = -0.5 * (coeff[1] / coeff[0]);
    }
    if (discr > 0)
    {
        root = coeff[1] > 0 ? -0.5 * (coeff[1] + sqrt(discr)) : -0.5 * (coeff[1] - sqrt(discr));
        dist[0] = root / coeff[0];
        dist[1] = coeff[2] / root;
    }
    return (1);
}

float   trim_cyl(t_vec *orig, t_vec *dir, t_cyl *cyl, float *dist)
{
    float   closest;

    closest = dist[0] > dist[1] ? dist[1] : dist[0];
    if (closest < 0 || !(in_height(orig, dir, cyl, closest)))
    {
        closest = dist[1] > dist[0] ? dist[1] : dist[0];
        if (closest < 0 || !(in_height(orig, dir, cyl, closest)))
            return (0);
    }
    return (closest);
}

int     in_height(t_vec *orig, t_vec *dir, t_cyl *cyl, float closest)
{
    t_vec   *hit_p;
    t_vec   *point;
    t_vec   *hit_proec;
    t_vec   *p_on_height;
    t_vec   *norm;
    float   proec_val;

    hit_p = vec_multipl_on(dir, closest);
    point = vec_addition(orig, hit_p);
    hit_proec = vec_subtract(point, cyl->bottom_p);
    proec_val = dot_product(hit_proec, cyl->orient);
    if (proec_val < 0 || proec_val > cyl->height)
        return (0);
    p_on_height = vec_multipl_on(cyl->orient, proec_val);
    norm = vec_subtract(point, p_on_height);
    vec_normalize(norm);
    cyl->norm->u = norm->n < 0 ? norm->u * (-1) : norm->u;
    cyl->norm->v = norm->n < 0 ? norm->v * (-1) : norm->v;
    cyl->norm->n = norm->n < 0 ? norm->n * (-1) : norm->n;
    free(hit_p);
    free(point);
    free(hit_proec);
    free(p_on_height);
    free(norm);
    return (1);
}