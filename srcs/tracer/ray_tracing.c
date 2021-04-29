/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:51:25 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 22:00:00 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			ray_tracing(unsigned int *addr, t_scene *scene, int size_line)
{
	t_vplane	*vplane;
	t_closest	*closest;
	int			j;
	float		y;
	float		x;

	vplane = get_vplane(scene->resolution_x, scene->resolution_y,
			scene->cam_lst->fov);
	closest = new_closest();
	j = scene->resolution_y - 1;
	y = -1;
	while (++y < scene->resolution_y)
	{
		x = -1;
		while (++x < scene->resolution_x)
		{
			canvas_to_vplane(y, x, closest, vplane);
			addr[(((j * (size_line / 4)) + (int)x))] = (unsigned int)
				(all_intersects(closest, scene));
		}
		j--;
	}
	free(vplane);
	free(closest);
}

t_vplane		*get_vplane(float width, float hight, float fov)
{
	t_vplane	*vplane;
	float		horizon;
	float		aspect_ratio;

	vplane = malloc(sizeof(t_vplane));
	if (!vplane)
		error_exit(-2);
	horizon = tan((fov / 2) * (M_PI / 180));
	horizon *= 2;
	aspect_ratio = width / hight;
	vplane->port_width = horizon;
	vplane->port_hight = horizon / aspect_ratio;
	vplane->x = vplane->port_width / width;
	vplane->y = vplane->port_hight / hight;
	vplane->scene_width = width;
	vplane->scene_hight = hight;
	return (vplane);
}

void			canvas_to_vplane(float y, float x, t_closest *closest,
		t_vplane *vplane)
{
	float	new_y;
	float	new_x;

	new_y = (y - (vplane->scene_hight / 2)) * vplane->y;
	new_x = (x - (vplane->scene_width / 2)) * vplane->x;
	closest->y = new_y;
	closest->x = new_x;
}
