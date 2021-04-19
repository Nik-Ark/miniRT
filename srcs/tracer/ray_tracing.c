/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:51:25 by lessie            #+#    #+#             */
/*   Updated: 2021/02/13 02:43:40 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			ray_tracing(void *mlx, void *window, t_scene *scene)
{
	int			color;
	t_vplane	*vplane;
	t_closest	*closest;
	int			i;
	int			j;
	float		y;
	float		x;

	vplane = get_vplane(scene->resolution_x, scene->resolution_y, scene->cam_lst->fov);
	closest = new_closest();
	j = scene->resolution_y;
	y = 0;
	while (j >= 0)
	{
		i = 0;
		x = 0;
		while (i <= scene->resolution_x)
		{
			canvas_to_vplane(y, x, closest, vplane);
			color = all_intersects(closest, scene);
			mlx_pixel_put(mlx, window, i, j,  color);     // TRY TO USE (int)x INSTEAD OF i
			i++;
			x++;
		}
		j--;
		y++;
	}
	t_cam		*cam = scene->cam_lst;
	t_sphere	*sphere = scene->sp_lst;
	printf("OriginU = %f OriginDirU = %f \nTransformed: mtrix_U = u %f v %f n %f\n", cam->origin->u, cam->dir->u, cam->matrix_u->u, cam->matrix_u->v, cam->matrix_u->n);
	printf("OriginV = %f OriginDirV = %f \nTransformed: mtrix_V = u %f v %f n %f\n", cam->origin->v, cam->dir->v, cam->matrix_v->u, cam->matrix_v->v, cam->matrix_v->n);
	printf("OriginN = %f OriginDirN = %f \nTransformed: mtrix_N = u %f v %f n %f\n", cam->origin->n, cam->dir->n, cam->matrix_n->u, cam->matrix_n->v, cam->matrix_n->n);

	free(vplane);
	free(closest);
	free(cam);
	free(sphere);
	free(scene); // Unite all free functions in one free function for everything
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

void			canvas_to_vplane(float y, float x, t_closest *closest, t_vplane *vplane)
{
	float	new_y;
	float	new_x;

	new_y = (y - (vplane->scene_hight / 2)) * vplane->y;
	new_x = (x - (vplane->scene_width / 2)) * vplane->x;
	closest->y = new_y;
	closest->x = new_x;
}
