/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:28:49 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:12:26 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# define TRIANGLE 3

# include "vec_stack.h"

typedef struct		s_triang
{
	t_vec			*vert_1_w;
	t_vec			*vert_2_w;
	t_vec			*vert_3_w;
	t_vst			vert_1;
	t_vst			vert_2;
	t_vst			vert_3;
	t_vst			edge_1;
	t_vst			edge_2;
	t_vst			norm;
	int				color;
	struct s_triang	*next;
}					t_triang;

void				compare_vert(t_triang *triang);
t_triang			*new_triang(t_vec *vert_1, t_vec *vert_2,
						t_vec *vert_3, int rgb);
void				transform_triangles(t_triang *tr_lst, t_cam *cam);
float				inter_triang(t_vst orig, t_vst dir, t_triang *triang);
void				check_triangles(t_closest *closest,
						t_scene *scene, t_vec *origin, t_vec *dir);
int					get_triang_light(t_closest *closest,
						t_scene *scene, t_vec *dir, t_colb *colb);

#endif
