/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:03:02 by lessie            #+#    #+#             */
/*   Updated: 2021/01/27 11:24:19 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

typedef struct		s_cam
{
	t_vec			*origin;
	t_vec			*dir;
    float			fov;
	t_vec			*matrix_u;
	t_vec			*matrix_v;
	t_vec			*matrix_n;
	float           **matrix_trans;
	float           **matrix_rotate;
	float           **matrix_w_to_cam;
	struct s_cam	*next;
}					t_cam;

t_cam				*new_cam(t_vec *origin, t_vec *dir, float fov);
void				cam_get_unit_vecs(t_cam *cam);
void                cam_get_matrix_trans(t_cam *cam);
void                cam_get_matrix_rotate(t_cam *cam);
void				free_cams(t_cam *cam);

#endif
