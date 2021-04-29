/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:59:45 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 21:54:40 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene		*new_scene(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		error_exit(-2);
	scene->sp_lst = NULL;
	scene->pl_lst = NULL;
	scene->tr_lst = NULL;
	scene->cyl_lst = NULL;
	scene->cam_lst = NULL;
	scene->light_lst = NULL;
	scene->amb = NULL;
	scene->colb = NULL;
	scene->resolution_x = 0;
	scene->resolution_y = 0;
	return (scene);
}

void		transform_scene(t_scene *scene, t_cam *cam)
{
	transform_spheres(scene->sp_lst, cam);
	transform_planes(scene->pl_lst, cam);
	transform_triangles(scene->tr_lst, cam);
	transform_cylinders(scene->cyl_lst, cam);
	transform_lights(scene->light_lst, cam);
}
