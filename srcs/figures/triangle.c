/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:28:00 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:29:11 by lessie           ###   ########.fr       */
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
	triang->color = rgb;
	triang->next = NULL;
	return (triang);
}

void		transform_triangles(t_triang *tr_lst, t_cam *cam)
{
	t_triang	*tmp;

	tmp = tr_lst;
	while (tmp)
	{
		tmp->vert_1 = vst_transform(tmp->vert_1_w, cam->matrix_w_to_cam);
		tmp->vert_2 = vst_transform(tmp->vert_2_w, cam->matrix_w_to_cam);
		tmp->vert_3 = vst_transform(tmp->vert_3_w, cam->matrix_w_to_cam);
		compare_vert(tmp);
		tmp->edge_1 = vst_subtract(tmp->vert_2, tmp->vert_1);
		tmp->edge_2 = vst_subtract(tmp->vert_3, tmp->vert_1);
		tmp->norm = vst_cross(tmp->edge_2, tmp->edge_1);
		tmp->norm = vst_norm_check(tmp->norm);
		tmp = tmp->next;
	}
}

void		compare_vert(t_triang *triang)
{
	t_vst	tmp_1;
	t_vst	tmp_2;
	t_vst	tmp_3;

	tmp_1 = triang->vert_1;
	tmp_2 = triang->vert_2;
	tmp_3 = triang->vert_3;
	if (tmp_1.u <= tmp_2.u && tmp_1.u <= tmp_3.u)
	{
		triang->vert_2 = tmp_3.u <= tmp_2.u ? tmp_3 : tmp_2;
		triang->vert_3 = tmp_3.u <= tmp_2.u ? tmp_2 : tmp_3;
	}
	else if (tmp_2.u <= tmp_1.u && tmp_2.u <= tmp_3.u)
	{
		triang->vert_2 = tmp_1.u <= tmp_3.u ? tmp_1 : tmp_3;
		triang->vert_3 = tmp_1.u <= tmp_3.u ? tmp_3 : tmp_1;
		triang->vert_1 = tmp_2;
	}
	else
	{
		triang->vert_2 = tmp_1.u <= tmp_2.u ? tmp_1 : tmp_2;
		triang->vert_3 = tmp_1.u <= tmp_2.u ? tmp_2 : tmp_1;
		triang->vert_1 = tmp_3;
	}
}

void		check_triangles(t_closest *closest, t_scene *scene,
		t_vec *origin, t_vec *dir)
{
	t_vst		orig_vst;
	t_vst		dir_vst;
	t_triang	*tmp;
	float		dist;

	tmp = scene->tr_lst;
	while (tmp)
	{
		orig_vst = new_vst(origin->u, origin->v, origin->n);
		dir_vst = new_vst(dir->u, dir->v, dir->n);
		dist = inter_triang(orig_vst, dir_vst, tmp);
		closest->type = (dist < closest->dist
				&& dist != 0) ? TRIANGLE : closest->type;
		closest->triang = (dist < closest->dist
				&& dist != 0) ? tmp : closest->triang;
		closest->dist = (dist < closest->dist
				&& dist != 0) ? dist : closest->dist;
		tmp = tmp->next;
	}
}

int			get_triang_light(t_closest *closest, t_scene *scene,
		t_vec *dir, t_colb *colb)
{
	int			rgb;
	t_light		*tmp;
	t_triang	*triang;
	t_vec		*tmp_dir;

	closest->to_amb = closest->dist;
	triang = closest->triang;
	tmp = scene->light_lst;
	colb->surf_p = vec_multipl_on(dir, (closest->dist - MIN));
	colb->surf_norm = new_vec(triang->norm.u, triang->norm.v, triang->norm.n);
	while (tmp)
	{
		tmp_dir = vec_subtract(tmp->origin, colb->surf_p);
		colb->to_light = vec_subtract(tmp->origin, colb->surf_p);
		colb->dist_to_light = vec_length(colb->to_light);
		closest->dist = colb->dist_to_light;
		check_all(closest, scene, colb->surf_p, tmp_dir);
		if (closest->type == 0)
			add_light_plane(colb, tmp, colb->surf_norm, colb->to_light);
		free_two(colb->to_light, tmp_dir);
		tmp = tmp->next;
	}
	rgb = add_figure_color(colb, triang->color, closest->to_amb);
	colb_reset(colb, closest);
	return (rgb);
}
