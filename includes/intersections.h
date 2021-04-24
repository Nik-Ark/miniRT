/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 01:18:26 by lessie            #+#    #+#             */
/*   Updated: 2021/02/17 12:23:50 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# define MIN 0.0005

int		all_intersects(t_closest *closest, t_scene *scene);
int		trace_ray(t_closest *closest, t_scene *scene, t_vec *origin, t_vec *dir);
void	check_all(t_closest *closest, t_scene *scene, t_vec *origin, t_vec *dir);
int		get_lightning(t_closest *closest, t_scene *scene, t_vec *dir);
int		add_figure_color(t_colb *colb, int figure_rgb, float to_cam_amb);

#endif
