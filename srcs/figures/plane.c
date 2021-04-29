/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:37:51 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:28:19 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*new_plane(t_vec *center, t_vec *normal, int color)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		error_exit(-2);
	plane->center_w = center;
	plane->normal_w = normal;
	plane->center = new_vec(0, 0, 0);
	plane->normal = new_vec(0, 0, 0);
	plane->color = color;
	plane->next = NULL;
	return (plane);
}

void	transform_planes(t_plane *pl_lst, t_cam *cam)
{
	t_plane	*tmp;

	tmp = pl_lst;
	while (tmp)
	{
		free(tmp->center);
		free(tmp->normal);
		tmp->center = vec_transform(tmp->center_w, cam->matrix_w_to_cam);
		tmp->normal = vec_transform(tmp->normal_w, cam->matrix_rotate);
		if (tmp->normal->n < 0)
		{
			tmp->normal->u = tmp->normal->u * (-1);
			tmp->normal->v = tmp->normal->v * (-1);
			tmp->normal->n = tmp->normal->n * (-1);
		}
		tmp = tmp->next;
	}
}

void	check_planes(t_closest *closest, t_scene *scene,
		t_vec *origin, t_vec *dir)
{
	t_plane	*tmp;
	float	dist;

	tmp = scene->pl_lst;
	while (tmp)
	{
		dist = inter_plane(origin, dir, tmp);
		closest->type = (dist < closest->dist
				&& dist != 0) ? PLANE : closest->type;
		closest->plane = (dist < closest->dist
				&& dist != 0) ? tmp : closest->plane;
		closest->dist = (dist < closest->dist
				&& dist != 0) ? dist : closest->dist;
		tmp = tmp->next;
	}
}

int		get_plane_light(t_closest *closest, t_scene *scene,
		t_vec *dir, t_colb *colb)
{
	int		rgb;
	t_light	*tmp;
	t_plane	*plane;
	t_vec	*tmp_dir;

	closest->to_amb = closest->dist;
	plane = closest->plane;
	tmp = scene->light_lst;
	colb->surf_p = vec_multipl_on(dir, (closest->dist - MIN));
	colb->surf_norm = vec_clone(plane->normal);
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
	rgb = add_figure_color(colb, plane->color, closest->to_amb);
	colb_reset(colb, closest);
	return (rgb);
}

void	add_light_plane(t_colb *colb, t_light *light,
		t_vec *surf_norm, t_vec *to_light)
{
	float	flare_angle;
	t_vec	*half;
	t_vec	*to_eye_vec;

	to_eye_vec = vec_multipl_on(colb->surf_p, -1);
	half = vec_addition(to_eye_vec, to_light);
	vec_normalize(half);
	vec_normalize(to_light);
	flare_angle = dot_product(surf_norm, half);
	add_color(colb, light, 1.0, 1.0);
	if (flare_angle > MIN)
		add_color(colb, light, powf(flare_angle, 256), 4.0);
	free_two(to_eye_vec, half);
}
