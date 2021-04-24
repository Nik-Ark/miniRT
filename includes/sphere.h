/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:31:58 by lessie            #+#    #+#             */
/*   Updated: 2021/02/12 10:50:16 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# define SPHERE 1

# include "vector.h"
# include "camera.h"
# include "closest.h"
# include "scene.h"
# include "light.h"

typedef struct		s_sphere
{
	t_vec			*center_w;
	t_vec           *center;
	float			radius;
	int				color;
	struct s_sphere	*next;
}					t_sphere;

t_sphere			*new_sphere(t_vec *center, float radius, int color);
void                transform_spheres(t_sphere *sp_lst, t_cam *cam);
float	            inter_sphere(t_vec *origin, t_vec *dir, t_sphere *sphere);
void	            check_spheres(t_closest *closest, t_scene *scene, t_vec *origin, t_vec *dir);
int		            get_sphere_light(t_closest *closest, t_scene *scene, t_vec *dir, t_colb *colb);
void	            add_light_sp(t_colb *colb, t_light *light, t_vec *surf_norm, t_vec *to_light);

#endif
