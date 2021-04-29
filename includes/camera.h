/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:03:02 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:09:26 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

typedef struct		s_cam
{
	void			*img;
	struct s_vec	*origin;
	struct s_vec	*dir;
	float			fov;
	struct s_vec	*matrix_u;
	struct s_vec	*matrix_v;
	struct s_vec	*matrix_n;
	float			**matrix_trans;
	float			**matrix_rotate;
	float			**matrix_w_to_cam;
	struct s_cam	*next;
	struct s_cam	*prev;
}					t_cam;

t_cam				*new_cam(struct s_vec *origin,
						struct s_vec *dir, float fov);
void				cam_get_unit_vecs(t_cam *cam);
void				cam_get_matrix_trans(t_cam *cam);
void				cam_get_matrix_rotate(t_cam *cam);

#endif
