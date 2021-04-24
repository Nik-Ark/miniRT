/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:28:49 by lessie            #+#    #+#             */
/*   Updated: 2021/02/17 11:37:15 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# define TRIANGLE 3

typedef struct		s_triang
{
	t_vec			*vert_1_w;
	t_vec			*vert_2_w;
	t_vec			*vert_3_w;
    t_vec			*vert_1;
    t_vec			*vert_2;
    t_vec			*vert_3;
	t_vec			*edge_1;
	t_vec			*edge_2;
	t_vec           *norm;
	int				color;
	struct s_triang	*next;
}					t_triang;

void                compare_vert(t_vec **vert_1, t_vec **vert_2, t_vec **vert_3);
t_triang			*new_triang(t_vec *vert_1, t_vec *vert_2, t_vec *vert_3, int rgb);
void                transform_triangles(t_triang *tr_lst, t_cam *cam);
float	            inter_triang(t_vec *orig, t_vec *dir, t_triang *triang);
void	            check_triangles(t_closest *closest, t_scene *scene, t_vec *origin, t_vec *dir);
int		            get_triang_light(t_closest *closest, t_scene *scene, t_vec *dir, t_colb *colb);

#endif
