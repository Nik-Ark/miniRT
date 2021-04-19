/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:29:26 by lessie            #+#    #+#             */
/*   Updated: 2021/04/08 15:29:37 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cyl   *new_cylinder(t_vec *bottom, t_vec *orient, float *diam_height, int rgb)
{
    t_cyl   *cyl;

    cyl = malloc(sizeof(t_cyl));
    if (!cyl)
        error_exit(-2);
    cyl->norm = new_vec(0, 0, 0);
    cyl->bottom_p_w = bottom;
    cyl->orient_w = orient;
    cyl->bottom_p = new_vec(0,0,0);
    cyl->orient = new_vec(0,0,0);
    cyl->radius = diam_height[0];
    cyl->height = diam_height[1];
    cyl->color = rgb;
    cyl->next = NULL;
    return (cyl);
}

void    transform_cylinders(t_cyl *cyl_lst, t_cam *cam)
{
    t_cyl   *tmp;

    tmp = cyl_lst;
    while (tmp)
    {
        free(tmp->bottom_p);
        free(tmp->orient);
        //printf("Cylinder point before: u = %f v = %f n = %f\n", tmp->bottom_p->u, tmp->bottom_p->v, tmp->bottom_p->n);
        //printf("Cylinder orient before: u = %f v = %f n = %f\n", tmp->orient->u, tmp->orient->v, tmp->orient->n);
        tmp->bottom_p = vec_transform(tmp->bottom_p_w, cam->matrix_w_to_cam);
        tmp->orient = vec_transform(tmp->orient_w, cam->matrix_rotate);
        /*
        if (tmp->orient->n < 0)
        {
            tmp->orient->u = tmp->orient->u * (-1);
            tmp->orient->v = tmp->orient->v * (-1);
            tmp->orient->n = tmp->orient->n * (-1);
        }
         */
        //printf("Cylinder point after: u = %f v = %f n = %f\n", tmp->bottom_p->u, tmp->bottom_p->v, tmp->bottom_p->n);
        //printf("Cylinder orient after: u = %f v = %f n = %f\n", tmp->orient->u, tmp->orient->v, tmp->orient->n);
        tmp = tmp->next;
    }
}

void    check_cylinders(t_closest *closest, t_scene *scene, t_vec *origin, t_vec *dir)
{
    t_cyl   *tmp;
    float   dist;

    tmp = scene->cyl_lst;
    while (tmp)
    {
        dist = inter_cylinder(origin, dir, tmp);
        closest->type = (dist < closest->dist && dist != 0) ? CYLINDER : closest->type;
        closest->cylinder = (dist < closest->dist && dist != 0) ? tmp : closest->cylinder;
        closest->dist = (dist < closest->dist && dist != 0) ? dist : closest->dist;
        tmp = tmp->next;
    }
}

int     get_cylinder_light(t_closest *closest, t_scene *scene, t_vec *dir, t_colb *colb)
{
    int			rgb;
    t_light		*tmp;
    t_cyl       *cyl;
    t_vec		*tmp_dir;
    float		to_cam_amb;

    to_cam_amb = closest->dist;
    cyl = closest->cylinder;
    tmp = scene->light_lst;
    colb->surf_p = vec_multipl_on(dir, (closest->dist - MIN)); // - MIN
    colb->surf_norm = new_vec(cyl->norm->u, cyl->norm->v, cyl->norm->n);
    while (tmp)
    {
        tmp_dir = vec_subtract(tmp->origin, colb->surf_p);
        colb->to_light = vec_subtract(tmp->origin, colb->surf_p);
        colb->dist_to_light = vec_length(colb->to_light);
        closest->dist = colb->dist_to_light;
        check_all(closest, scene, colb->surf_p, tmp_dir);
        if (closest->type == 0)
            add_light_cyl(colb, tmp, colb->surf_norm, colb->to_light);
        free(colb->to_light);
        free(tmp_dir);
        tmp = tmp->next;
    }
    rgb = add_figure_color(colb, cyl->color, to_cam_amb);
    colb_reset(colb);
    closest->type = 0;
    return (rgb);
}

void	add_light_cyl(t_colb *colb, t_light *light, t_vec *surf_norm, t_vec *to_light)
{
    float	light_angle;
    float	flare_angle;
    t_vec	*half;
    t_vec	*to_eye_vec;

    to_eye_vec = vec_multipl_on(colb->surf_p, -1);
    half = vec_addition(to_eye_vec, to_light);
    vec_normalize(to_light);
    vec_normalize(half);
    light_angle = dot_product(surf_norm, to_light);
    flare_angle = dot_product(surf_norm, half);
    colb->rgb->u += ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * get_r(light->rgb)) / 2;
    colb->rgb->v += ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * get_r(light->rgb)) / 2;
    colb->rgb->n += ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * get_r(light->rgb)) / 2;
    if (light_angle > 0)
    {
        colb->rgb->u += 4 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * light_angle) * get_r(light->rgb);
        colb->rgb->v += 4 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * light_angle) * get_g(light->rgb);
        colb->rgb->n += 4 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * light_angle) * get_b(light->rgb);
    }
    /*
    if (flare_angle > 0)
    {
        colb->rgb->u += 2 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * powf(flare_angle, 256)) * get_r(light->rgb);
        colb->rgb->v += 2 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * powf(flare_angle, 256)) * get_g(light->rgb);
        colb->rgb->n += 2 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * powf(flare_angle, 256)) * get_b(light->rgb);
    }
     */
    free(to_eye_vec);
    free(half);
}