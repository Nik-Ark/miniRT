/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:02:19 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:29:50 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*new_sphere(t_vec *center, float radius, int color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error_exit(-2);
	sphere->center_w = center;
	sphere->center = new_vec(0, 0, 0);
	sphere->radius = radius;
	sphere->color = color;
	sphere->next = NULL;
	return (sphere);
}

void		transform_spheres(t_sphere *sp_lst, t_cam *cam)
{
	t_sphere	*tmp;

	tmp = sp_lst;
	while (tmp)
	{
		free(tmp->center);
		tmp->center = vec_transform(tmp->center_w, cam->matrix_w_to_cam);
		tmp = tmp->next;
	}
}

void		check_spheres(t_closest *closest, t_scene *scene,
		t_vec *origin, t_vec *dir)
{
	t_sphere	*tmp;
	float		dist;

	tmp = scene->sp_lst;
	while (tmp)
	{
		dist = inter_sphere(origin, dir, tmp);
		closest->type = (dist < closest->dist
				&& dist != 0) ? SPHERE : closest->type;
		closest->sphere = (dist < closest->dist
				&& dist != 0) ? tmp : closest->sphere;
		closest->dist = (dist < closest->dist
				&& dist != 0) ? dist : closest->dist;
		tmp = tmp->next;
	}
}

int			get_sphere_light(t_closest *closest, t_scene *scene,
		t_vec *dir, t_colb *colb)
{
	int			rgb;
	t_light		*tmp;
	t_sphere	*sphere;
	t_vec		*tmp_dir;

	closest->to_amb = closest->dist;
	sphere = closest->sphere;
	tmp = scene->light_lst;
	colb->surf_p = vec_multipl_on(dir, (closest->dist - MIN));
	colb->surf_norm = sphere_norm(colb->surf_p, sphere->center);
	while (tmp)
	{
		tmp_dir = vec_subtract(tmp->origin, colb->surf_p);
		colb->to_light = vec_subtract(tmp->origin, colb->surf_p);
		colb->dist_to_light = vec_length(colb->to_light);
		closest->dist = colb->dist_to_light;
		check_all(closest, scene, colb->surf_p, tmp_dir);
		if (closest->type == 0)
			add_light_sp(colb, tmp, colb->surf_norm, colb->to_light);
		free_two(colb->to_light, tmp_dir);
		tmp = tmp->next;
	}
	rgb = add_figure_color(colb, sphere->color, closest->to_amb);
	colb_reset(colb, closest);
	return (rgb);
}

void		add_light_sp(t_colb *colb, t_light *light,
		t_vec *surf_norm, t_vec *to_light)
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
		add_color(colb, light, light_angle, 4.0);
	if (flare_angle > 0)
		add_color(colb, light, powf(flare_angle, 256), 16.0);
	free_two(to_eye_vec, half);
}
