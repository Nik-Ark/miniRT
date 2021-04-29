/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:31:09 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:12:46 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# define PLANE 2

typedef struct		s_plane
{
	t_vec			*center_w;
	t_vec			*normal_w;
	t_vec			*center;
	t_vec			*normal;
	int				color;
	struct s_plane	*next;
}					t_plane;

t_plane				*new_plane(t_vec *center, t_vec *normal, int color);
void				transform_planes(t_plane *pl_lst, t_cam *cam);
float				inter_plane(t_vec *origin, t_vec *dir, t_plane *plane);
void				check_planes(t_closest *closest,
						t_scene *scene, t_vec *origin, t_vec *dir);
int					get_plane_light(t_closest *closest,
						t_scene *scene, t_vec *dir, t_colb *colb);
void				add_light_plane(t_colb *colb, t_light *light,
						t_vec *surf_norm, t_vec *to_light);

#endif
