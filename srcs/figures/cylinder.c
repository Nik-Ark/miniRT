/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:29:26 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:27:40 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cyl	*new_cylinder(t_vec *bottom,
		t_vec *orient, const float *diam_height, int rgb)
{
	t_cyl	*cyl;

	cyl = malloc(sizeof(t_cyl));
	if (!cyl)
		error_exit(-2);
	cyl->bottom_p_w = bottom;
	cyl->orient_w = orient;
	cyl->radius = diam_height[0];
	cyl->height = diam_height[1];
	cyl->color = rgb;
	cyl->next = NULL;
	return (cyl);
}

void	transform_cylinders(t_cyl *cyl_lst, t_cam *cam)
{
	t_cyl	*tmp;

	tmp = cyl_lst;
	while (tmp)
	{
		tmp->bottom_p = vst_transform(tmp->bottom_p_w, cam->matrix_w_to_cam);
		tmp->orient = vst_transform(tmp->orient_w, cam->matrix_rotate);
		tmp = tmp->next;
	}
}

void	check_cylinders(t_closest *closest, t_scene *scene,
		t_vec *origin, t_vec *dir)
{
	t_vst	orig_vst;
	t_vst	dir_vst;
	t_cyl	*tmp;
	float	dist;

	tmp = scene->cyl_lst;
	while (tmp)
	{
		orig_vst = new_vst(origin->u, origin->v, origin->n);
		dir_vst = new_vst(dir->u, dir->v, dir->n);
		dist = inter_cylinder(orig_vst, dir_vst, tmp);
		closest->type = (dist < closest->dist
				&& dist != 0) ? CYLINDER : closest->type;
		closest->cylinder = (dist < closest->dist
				&& dist != 0) ? tmp : closest->cylinder;
		closest->dist = (dist < closest->dist
				&& dist != 0) ? dist : closest->dist;
		tmp = tmp->next;
	}
}

int		get_cylinder_light(t_closest *closest,
		t_scene *scene, t_vec *dir, t_colb *colb)
{
	int		rgb;
	t_light	*tmp;
	t_cyl	*cyl;
	t_vec	*tmp_dir;

	closest->to_amb = closest->dist;
	cyl = closest->cylinder;
	tmp = scene->light_lst;
	colb->surf_p = vec_multipl_on(dir, (closest->dist - MIN));
	colb->surf_norm = new_vec(cyl->norm.u, cyl->norm.v, cyl->norm.n);
	while (tmp)
	{
		tmp_dir = vec_subtract(tmp->origin, colb->surf_p);
		colb->to_light = vec_subtract(tmp->origin, colb->surf_p);
		colb->dist_to_light = vec_length(colb->to_light);
		closest->dist = colb->dist_to_light;
		check_all(closest, scene, colb->surf_p, tmp_dir);
		if (closest->type == 0)
			add_light_cyl(colb, tmp, colb->surf_norm, colb->to_light);
		free_two(colb->to_light, tmp_dir);
		tmp = tmp->next;
	}
	rgb = add_figure_color(colb, cyl->color, closest->to_amb);
	colb_reset(colb, closest);
	return (rgb);
}

void	add_light_cyl(t_colb *colb, t_light *light,
		t_vec *surf_norm, t_vec *to_light)
{
	float	light_angle;

	vec_normalize(to_light);
	light_angle = dot_product(surf_norm, to_light);
	colb->rgb->u += ((light->inten / (colb->dist_to_light
					* colb->dist_to_light)) * get_r(light->rgb)) / 2;
	colb->rgb->v += ((light->inten / (colb->dist_to_light
					* colb->dist_to_light)) * get_r(light->rgb)) / 2;
	colb->rgb->n += ((light->inten / (colb->dist_to_light
					* colb->dist_to_light)) * get_r(light->rgb)) / 2;
	if (light_angle > 0)
		add_color(colb, light, light_angle, 4.0);
}
