/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:28:00 by lessie            #+#    #+#             */
/*   Updated: 2021/02/17 10:45:31 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_triang	*new_triang(t_vec *vert_1, t_vec *vert_2, t_vec *vert_3, int rgb)
{
	t_triang	*triang;

	triang = malloc(sizeof(t_triang));
	if (!triang)
		error_exit(-2);
	triang->vert_1_w = vert_1;
	triang->vert_2_w = vert_2;
	triang->vert_3_w = vert_3;
    triang->vert_1 = new_vec(0,0,0);
    triang->vert_2 = new_vec(0,0,0);
    triang->vert_3 = new_vec(0,0,0);
	triang->edge_1 = new_vec(0,0,0);
	triang->edge_2 = new_vec(0,0,0);
	triang->norm = new_vec(0,0,0);
	triang->color = rgb;
	triang->next = NULL;
	return (triang);
}

void        transform_triangles(t_triang *tr_lst, t_cam *cam)
{
    t_triang    *tmp;

    tmp = tr_lst;
    while (tmp)
    {
        free(tmp->vert_1);
        free(tmp->vert_2);
        free(tmp->vert_3);
        free(tmp->edge_1);
        free(tmp->edge_2);
        free(tmp->norm);
        //printf("Triang Vert_1 before: u = %f v = %f n = %f\n", tmp->vert_1->u, tmp->vert_1->v, tmp->vert_1->n);
        //printf("Triang Vert_2 before: u = %f v = %f n = %f\n", tmp->vert_2->u, tmp->vert_2->v, tmp->vert_2->n);
        //printf("Triang Vert_3 before: u = %f v = %f n = %f\n", tmp->vert_3->u, tmp->vert_3->v, tmp->vert_3->n);
        tmp->vert_1 = vec_transform(tmp->vert_1_w, cam->matrix_w_to_cam);
        tmp->vert_2 = vec_transform(tmp->vert_2_w, cam->matrix_w_to_cam);
        tmp->vert_3 = vec_transform(tmp->vert_3_w, cam->matrix_w_to_cam);
        //printf("Old addresses: %p %p %p\n", &*(tmp->vert_1), &*(tmp->vert_2), &*(tmp->vert_3));
        compare_vert(&tmp->vert_1, &tmp->vert_2, &tmp->vert_3);
        //printf("New addresses: %p %p %p\n", &*(tmp->vert_1), &*(tmp->vert_2), &*(tmp->vert_3));
        tmp->edge_1 = vec_subtract(tmp->vert_2, tmp->vert_1);
        tmp->edge_2 = vec_subtract(tmp->vert_3, tmp->vert_1);
        tmp->norm = vec_cross(tmp->edge_2, tmp->edge_1);
        vec_normalize(tmp->norm);
        //printf("Triang normal after: u = %f v = %f n = %f\n", tmp->norm->u, tmp->norm->v, tmp->norm->n);
        //printf("Triang Vert_1 after: u = %f v = %f n = %f\n", tmp->vert_1->u, tmp->vert_1->v, tmp->vert_1->n);
        //printf("Triang Vert_2 after: u = %f v = %f n = %f\n", tmp->vert_2->u, tmp->vert_2->v, tmp->vert_2->n);
        //printf("Triang Vert_3 after: u = %f v = %f n = %f\n", tmp->vert_3->u, tmp->vert_3->v, tmp->vert_3->n);
        //printf("Triang Edge_1 after: u = %f v = %f n = %f\n", tmp->edge_1->u, tmp->edge_1->v, tmp->edge_1->n);
        //printf("Triang Edge_2 after: u = %f v = %f n = %f\n", tmp->edge_2->u, tmp->edge_2->v, tmp->edge_2->n);
        tmp = tmp->next;
    }
}

void        compare_vert(t_vec **vert_1, t_vec **vert_2, t_vec **vert_3)
{
    t_vec   *tmp_1;
    t_vec   *tmp_2;
    t_vec   *tmp_3;

    tmp_1 = *vert_1;
    tmp_2 = *vert_2;
    tmp_3 = *vert_3;
    if (tmp_1->u < tmp_2->u && tmp_1->u < tmp_3->u)
    {
        *vert_2 = tmp_3->u < tmp_2->u ? tmp_3 : tmp_2;
        *vert_3 = tmp_3->u < tmp_2->u ? tmp_2 : tmp_3;
    }
    else if (tmp_2->u < tmp_1->u && tmp_2->u < tmp_3->u)
    {
        *vert_2 = tmp_1->u < tmp_3->u ? tmp_1 : tmp_3;
        *vert_3 = tmp_1->u < tmp_3->u ? tmp_3 : tmp_1;
        *vert_1 = tmp_2;
    }
    else
    {
        *vert_2 = tmp_1->u < tmp_2->u ? tmp_1 : tmp_2;
        *vert_3 = tmp_1->u < tmp_2->u ? tmp_2 : tmp_1;
        *vert_1 = tmp_3;
    }
}

void	check_triangles(t_closest *closest, t_scene *scene, t_vec *origin, t_vec *dir)
{
    t_triang	*tmp;
    float		dist;

    tmp = scene->tr_lst;
    while (tmp)
    {
        dist = inter_triang(origin, dir, tmp);
        closest->type = (dist < closest->dist && dist != 0) ? TRIANGLE : closest->type;
        closest->triang = (dist < closest->dist && dist != 0) ? tmp : closest->triang;
        closest->dist = (dist < closest->dist && dist != 0) ? dist : closest->dist;
        tmp = tmp->next;
    }
}

int		get_triang_light(t_closest *closest, t_scene *scene, t_vec *dir, t_colb *colb)
{
    int			rgb;
    t_light		*tmp;
    t_triang	*triang;
    t_vec		*tmp_dir;
    float		to_cam_amb;

    to_cam_amb = closest->dist;
    triang = closest->triang;
    tmp = scene->light_lst;
    colb->surf_p = vec_multipl_on(dir, (closest->dist - MIN));
    colb->surf_norm = new_vec(triang->norm->u, triang->norm->v, triang->norm->n);
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
    rgb = add_figure_color(colb, triang->color, to_cam_amb);
    colb_reset(colb);
    closest->type = 0;
    return (rgb);
}