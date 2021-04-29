/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_intersects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 11:01:52 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:32:58 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		all_intersects(t_closest *closest, t_scene *scene)
{
	int		rgb;
	t_vec	*origin;
	t_vec	*dir;

	origin = new_vec(0, 0, 0);
	dir = new_vec(closest->x, closest->y, -1);
	rgb = trace_ray(closest, scene, origin, dir);
	free(origin);
	free(dir);
	return (rgb);
}

int		trace_ray(t_closest *closest, t_scene *scene, t_vec *origin, t_vec *dir)
{
	int		rgb;

	rgb = BACKGROUND;
	closest->dist = 99999999;
	check_all(closest, scene, origin, dir);
	if (closest->type != 0)
		rgb = get_lightning(closest, scene, dir);
	return (rgb);
}

void	check_all(t_closest *closest, t_scene *scene, t_vec *origin, t_vec *dir)
{
	closest->type = 0;
	vec_normalize(dir);
	check_spheres(closest, scene, origin, dir);
	check_planes(closest, scene, origin, dir);
	check_triangles(closest, scene, origin, dir);
	check_cylinders(closest, scene, origin, dir);
}

int		get_lightning(t_closest *closest, t_scene *scene, t_vec *dir)
{
	int	rgb;

	rgb = 0;
	rgb = closest->type == SPHERE ? get_sphere_light(closest,
		scene, dir, scene->colb) : rgb;
	rgb = closest->type == PLANE ? get_plane_light(closest,
		scene, dir, scene->colb) : rgb;
	rgb = closest->type == TRIANGLE ? get_triang_light(closest,
		scene, dir, scene->colb) : rgb;
	rgb = closest->type == CYLINDER ? get_cylinder_light(closest,
		scene, dir, scene->colb) : rgb;
	return (rgb);
}

int		add_figure_color(t_colb *colb, int figure_rgb, float to_cam_amb)
{
	float	r;
	float	g;
	float	b;

	r = get_r(figure_rgb) * (colb->rgb->u + (colb->amb->u
				/ (to_cam_amb * to_cam_amb)));
	r = r > 255 ? 255 : r;
	r = r < 0 ? 0 : r;
	g = get_g(figure_rgb) * (colb->rgb->v + (colb->amb->v
				/ (to_cam_amb * to_cam_amb)));
	g = g > 255 ? 255 : g;
	g = g < 0 ? 0 : g;
	b = get_b(figure_rgb) * (colb->rgb->n + (colb->amb->n
				/ (to_cam_amb * to_cam_amb)));
	b = b > 255 ? 255 : b;
	b = b < 0 ? 0 : b;
	return (create_rgb(r, g, b));
}
