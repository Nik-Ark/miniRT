/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:02:19 by lessie            #+#    #+#             */
/*   Updated: 2021/02/12 10:51:32 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere		*new_sphere(t_vec *center, float radius, int color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error_exit(-2);
	sphere->center_w = center;
	sphere->center = new_vec(0,0,0);
	sphere->radius = radius;
	sphere->color = color;
	sphere->next = NULL;
	return (sphere);
}

void            transform_spheres(t_sphere *sp_lst, t_cam *cam)
{
    t_sphere    *tmp;

    tmp = sp_lst;
    while (tmp)
    {
        free(tmp->center);
        //printf("Sphere before: u = %f v = %f n = %f\n", tmp->center->u, tmp->center->v, tmp->center->n);
        tmp->center = vec_transform(tmp->center_w, cam->matrix_w_to_cam);
        //printf("Sphere after: u = %f v = %f n = %f\n", tmp->center->u, tmp->center->v, tmp->center->n);
        tmp = tmp->next;
    }
}

void	check_spheres(t_closest *closest, t_scene *scene, t_vec *origin, t_vec *dir)
{
    t_sphere	*tmp;
    float		dist;

    tmp = scene->sp_lst;
    while (tmp)
    {
        dist = inter_sphere(origin, dir, tmp);
        closest->type = (dist < closest->dist && dist != 0) ? SPHERE : closest->type;
        closest->sphere = (dist < closest->dist && dist != 0) ? tmp : closest->sphere;
        closest->dist = (dist < closest->dist && dist != 0) ? dist : closest->dist;
        tmp = tmp->next;
    }
}

int		get_sphere_light(t_closest *closest, t_scene *scene, t_vec *dir, t_colb *colb)
{
    int			rgb;
    t_light		*tmp;
    t_sphere	*sphere;
    t_vec		*tmp_dir;
    float		to_cam_amb;

    to_cam_amb = closest->dist;
    sphere = closest->sphere;
    tmp = scene->light_lst;
    colb->surf_p = vec_multipl_on(dir, (closest->dist - MIN)); // - MIN ???
    vec_normalize(colb->surf_norm = vec_subtract(colb->surf_p, sphere->center));
    while (tmp)
    {
        tmp_dir = vec_subtract(tmp->origin, colb->surf_p);
        colb->to_light = vec_subtract(tmp->origin, colb->surf_p);
        colb->dist_to_light = vec_length(colb->to_light);
        closest->dist = colb->dist_to_light;
        check_all(closest, scene, colb->surf_p, tmp_dir);
        if (closest->type == 0)
            add_light_sp(colb, tmp, colb->surf_norm, colb->to_light);
        free(colb->to_light);
        free(tmp_dir);
        tmp = tmp->next;
    }
    rgb = add_figure_color(colb, sphere->color, to_cam_amb);
    colb_reset(colb); // REBUILD FUNCTION TO RESET COLB AND CLOSEST->TYPE TO ZERO (0)
    closest->type = 0;
    return (rgb);
}

void	add_light_sp(t_colb *colb, t_light *light, t_vec *surf_norm, t_vec *to_light)
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
    if (light_angle > 0)
    {
        colb->rgb->u += 4 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * light_angle) * get_r(light->rgb);
        colb->rgb->v += 4 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * light_angle) * get_g(light->rgb);
        colb->rgb->n += 4 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * light_angle) * get_b(light->rgb);
    }
    if (flare_angle > 0)
    {
        colb->rgb->u += 16 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * powf(flare_angle, 256)) * get_r(light->rgb);
        colb->rgb->v += 16 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * powf(flare_angle, 256)) * get_g(light->rgb);
        colb->rgb->n += 16 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * powf(flare_angle, 256)) * get_b(light->rgb);
    }
    free(to_eye_vec);
    free(half);
}