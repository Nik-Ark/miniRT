/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:37:51 by lessie            #+#    #+#             */
/*   Updated: 2021/02/15 17:10:44 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane		*new_plane(t_vec *center, t_vec *normal, int color)
{
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		error_exit(-2);
	plane->center_w = center;
	plane->normal_w = normal;
    plane->center = new_vec(0,0,0);
    plane->normal = new_vec(0,0,0);
	plane->color = color;
	plane->next = NULL;
	return (plane);
}

void        transform_planes(t_plane *pl_lst, t_cam *cam)
{
    t_plane     *tmp;

    tmp = pl_lst;
    while (tmp)
    {
        free(tmp->center);
        free(tmp->normal);
		//printf("Plane point before: u = %f v = %f n = %f\n", tmp->center->u, tmp->center->v, tmp->center->n);
		//printf("Plane normal before: u = %f v = %f n = %f\n", tmp->normal->u, tmp->normal->v, tmp->normal->n);
        tmp->center = vec_transform(tmp->center_w, cam->matrix_w_to_cam);
        tmp->normal = vec_transform(tmp->normal_w, cam->matrix_rotate);
        if (tmp->normal->n < 0)
        {
            tmp->normal->u = tmp->normal->u * (-1);
            tmp->normal->v = tmp->normal->v * (-1);
            tmp->normal->n = tmp->normal->n * (-1);
        }
		//printf("Plane point after: u = %f v = %f n = %f\n", tmp->center->u, tmp->center->v, tmp->center->n);
		//printf("Plane normal after: u = %f v = %f n = %f\n", tmp->normal->u, tmp->normal->v, tmp->normal->n);
        tmp = tmp->next;
    }
}

void	check_planes(t_closest *closest, t_scene *scene, t_vec *origin, t_vec *dir)
{
    t_plane		*tmp;
    float		dist;

    tmp = scene->pl_lst;
    while (tmp)
    {
        dist = inter_plane(origin, dir, tmp);
        closest->type = (dist < closest->dist && dist != 0) ? PLANE : closest->type;
        closest->plane = (dist < closest->dist && dist != 0) ? tmp : closest->plane;
        closest->dist = (dist < closest->dist && dist != 0) ? dist : closest->dist;
        tmp = tmp->next;
    }
}

int		get_plane_light(t_closest *closest, t_scene *scene, t_vec *dir, t_colb *colb)
{
    int			rgb;
    t_light		*tmp;
    t_plane		*plane;
    t_vec		*tmp_dir;
    float		to_cam_amb;

    to_cam_amb = closest->dist;
    plane = closest->plane;
    tmp = scene->light_lst;
    colb->surf_p = vec_multipl_on(dir, (closest->dist - MIN));
    colb->surf_norm = new_vec(plane->normal->u, plane->normal->v, plane->normal->n);
    while (tmp)
    {
        tmp_dir = vec_subtract(tmp->origin, colb->surf_p);
        colb->to_light = vec_subtract(tmp->origin, colb->surf_p);
        colb->dist_to_light = vec_length(colb->to_light);
        closest->dist = colb->dist_to_light;
        check_all(closest, scene, colb->surf_p, tmp_dir);
        if (closest->type == 0)
            add_light_plane(colb, tmp, colb->surf_norm, colb->to_light);
        free(colb->to_light);
        free(tmp_dir);
        tmp = tmp->next;
    }
    rgb = add_figure_color(colb, plane->color, to_cam_amb);
    colb_reset(colb);
    closest->type = 0;
    return (rgb);
}

void	add_light_plane(t_colb *colb, t_light *light, t_vec *surf_norm, t_vec *to_light)
{
    float	flare_angle;
    t_vec	*half;
    t_vec	*to_eye_vec;

    to_eye_vec = vec_multipl_on(colb->surf_p, -1);
    half = vec_addition(to_eye_vec, to_light);
    vec_normalize(half);
    vec_normalize(to_light); // TRY TO MOVE IT ABOVE HALF WHEN TEST WITH PLANES
    flare_angle = dot_product(surf_norm, half);
    colb->rgb->u += (light->inten / (colb->dist_to_light * colb->dist_to_light)) * get_r(light->rgb);
    colb->rgb->v += (light->inten / (colb->dist_to_light * colb->dist_to_light)) * get_r(light->rgb);
    colb->rgb->n += (light->inten / (colb->dist_to_light * colb->dist_to_light)) * get_r(light->rgb);
    if (flare_angle > MIN)
    {
        colb->rgb->u += 4 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * powf(flare_angle, 256)) * get_r(light->rgb);
        colb->rgb->v += 4 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * powf(flare_angle, 256)) * get_g(light->rgb);
        colb->rgb->n += 4 * ((light->inten / (colb->dist_to_light * colb->dist_to_light)) * powf(flare_angle, 256)) * get_b(light->rgb);
    }
    free(to_eye_vec);
    free(half);
}