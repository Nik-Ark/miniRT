/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 13:52:45 by lessie            #+#    #+#             */
/*   Updated: 2021/02/17 10:26:38 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef struct      s_scene
{
	struct s_sphere *sp_lst;
	struct s_plane  *pl_lst;
	struct s_triang *tr_lst;
	struct s_cyl    *cyl_lst;
	struct s_cam    *cam_lst;
	struct s_light  *light_lst;
	struct s_amb    *amb;
	struct s_colb   *colb;
	float		    resolution_x;
	float		    resolution_y;
}				    t_scene;

t_scene			    *new_scene();
void                transform_scene(t_scene *scene, t_cam *cam);
//free_scene(); frees every list of objects and frees scene........

#endif
