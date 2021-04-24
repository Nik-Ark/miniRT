/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:53:30 by lessie            #+#    #+#             */
/*   Updated: 2021/01/30 16:01:32 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACING_H
# define RAY_TRACING_H

typedef struct	s_vplane
{
	float		scene_width;
	float		scene_hight;
	float		port_width;
	float		port_hight;
	float		x;
	float		y;
}				t_vplane;

void			ray_tracing(int *addr, t_scene *scene);
t_vplane		*get_vplane(float width, float hight, float fov);
void			canvas_to_vplane(float y, float x, t_closest *closest, t_vplane *vplane);

#endif
