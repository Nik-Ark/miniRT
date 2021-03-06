/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:30:09 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:12:11 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# define CYLINDER 5

typedef struct		s_cyl
{
	t_vec			*bottom_p_w;
	t_vec			*orient_w;
	t_vst			bottom_p;
	t_vst			orient;
	t_vst			norm;
	float			radius;
	float			height;
	int				color;
	struct s_cyl	*next;
}					t_cyl;

t_cyl				*new_cylinder(t_vec *bottom,
						t_vec *orient, const float *diam_height, int rgb);
void				transform_cylinders(t_cyl *cyl_lst, t_cam *cam);
float				inter_cylinder(t_vst orig, t_vst dir, t_cyl *cyl);
void				get_coeff(t_vst orig, t_vst dir, t_cyl *cyl, float *coeff);
int					cyl_equation(const float *coeff, float *dist);
float				trim_cyl(t_vst orig, t_vst dir,
						t_cyl *cyl, const float *dist);
int					in_height(t_vst orig, t_vst dir,
						t_cyl *cyl, float closest);
void				check_cylinders(t_closest *closest,
						t_scene *scene, t_vec *origin, t_vec *dir);
int					get_cylinder_light(t_closest *closest,
						t_scene *scene, t_vec *dir, t_colb *colb);
void				add_light_cyl(t_colb *colb,
						t_light *light, t_vec *surf_norm, t_vec *to_light);

#endif
