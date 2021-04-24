/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:15:04 by lessie            #+#    #+#             */
/*   Updated: 2021/01/27 11:24:15 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam	*new_cam(t_vec *origin, t_vec *dir,	float fov)
{
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	if (!cam)
		error_exit(-2);
	cam->img = NULL;
	cam->origin = origin;
	cam->dir = dir;
    cam->fov = fov;
    cam->next = NULL;
    cam->prev = NULL;
    cam_get_unit_vecs(cam);
    cam_get_matrix_trans(cam);
    cam_get_matrix_rotate(cam);
    cam->matrix_w_to_cam = matrix_multiply(cam->matrix_trans, cam->matrix_rotate, 4);
    printf("Matrix W2C:\n %f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
           cam->matrix_w_to_cam[0][0], cam->matrix_w_to_cam[0][1], cam->matrix_w_to_cam[0][2], cam->matrix_w_to_cam[0][3],
           cam->matrix_w_to_cam[1][0], cam->matrix_w_to_cam[1][1], cam->matrix_w_to_cam[1][2], cam->matrix_w_to_cam[1][3],
           cam->matrix_w_to_cam[2][0], cam->matrix_w_to_cam[2][1], cam->matrix_w_to_cam[2][2], cam->matrix_w_to_cam[2][3],
           cam->matrix_w_to_cam[3][0], cam->matrix_w_to_cam[3][1], cam->matrix_w_to_cam[3][2], cam->matrix_w_to_cam[3][3]);
	return (cam);
}

void	cam_get_unit_vecs(t_cam *cam)
{
    t_vec	*tmp;

    cam->matrix_n = vec_subtract(cam->origin, cam->dir);
    vec_normalize(cam->matrix_n);
    if ((cam->matrix_n->v == 1) || (cam->matrix_n->v == -1))
        tmp = (cam->matrix_n->v == 1) ? new_vec(0,0,-1) : new_vec(0, 0, 1);
    else
        tmp = new_vec(0,1,0);
    cam->matrix_u = vec_cross(tmp, cam->matrix_n);
    vec_normalize(cam->matrix_u);
    cam->matrix_v = vec_cross(cam->matrix_n, cam->matrix_u);
    free(tmp);
}

void    cam_get_matrix_trans(t_cam *cam)
{
    cam->matrix_trans = get_matrix_rows(4);
    cam->matrix_trans[0][0] = 1;
    cam->matrix_trans[1][1] = 1;
    cam->matrix_trans[2][2] = 1;
    cam->matrix_trans[3][3] = 1;
    cam->matrix_trans[0][3] = -(cam->origin->u);
    cam->matrix_trans[1][3] = -(cam->origin->v);
    cam->matrix_trans[2][3] = -(cam->origin->n);
    printf("Matrix Trans:\n %f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
           cam->matrix_trans[0][0], cam->matrix_trans[0][1], cam->matrix_trans[0][2], cam->matrix_trans[0][3],
           cam->matrix_trans[1][0], cam->matrix_trans[1][1], cam->matrix_trans[1][2], cam->matrix_trans[1][3],
           cam->matrix_trans[2][0], cam->matrix_trans[2][1], cam->matrix_trans[2][2], cam->matrix_trans[2][3],
           cam->matrix_trans[3][0], cam->matrix_trans[3][1], cam->matrix_trans[3][2], cam->matrix_trans[3][3]);
}

void    cam_get_matrix_rotate(t_cam *cam)
{
    cam->matrix_rotate = get_matrix_rows(4);
    cam->matrix_rotate[3][3] = 1;
    cam->matrix_rotate[0][0] = cam->matrix_u->u;
    cam->matrix_rotate[0][1] = cam->matrix_u->v;
    cam->matrix_rotate[0][2] = cam->matrix_u->n;
    cam->matrix_rotate[1][0] = cam->matrix_v->u;
    cam->matrix_rotate[1][1] = cam->matrix_v->v;
    cam->matrix_rotate[1][2] = cam->matrix_v->n;
    cam->matrix_rotate[2][0] = cam->matrix_n->u;
    cam->matrix_rotate[2][1] = cam->matrix_n->v;
    cam->matrix_rotate[2][2] = cam->matrix_n->n;
    printf("Matrix Rotate:\n %f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
           cam->matrix_rotate[0][0], cam->matrix_rotate[0][1], cam->matrix_rotate[0][2], cam->matrix_rotate[0][3],
           cam->matrix_rotate[1][0], cam->matrix_rotate[1][1], cam->matrix_rotate[1][2], cam->matrix_rotate[1][3],
           cam->matrix_rotate[2][0], cam->matrix_rotate[2][1], cam->matrix_rotate[2][2], cam->matrix_rotate[2][3],
           cam->matrix_rotate[3][0], cam->matrix_rotate[3][1], cam->matrix_rotate[3][2], cam->matrix_rotate[3][3]);
}