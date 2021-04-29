/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:42:35 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:13:41 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

typedef struct		s_light
{
	int				rgb;
	float			inten;
	t_vec			*origin_w;
	t_vec			*origin;
	struct s_light	*next;
}					t_light;

typedef struct		s_amb
{
	int				rgb;
	float			inten;
}					t_amb;

typedef struct		s_colb
{
	t_vec			*amb;
	t_vec			*rgb;
	t_vec			*surf_p;
	t_vec			*surf_norm;
	t_vec			*to_light;
	float			dist_to_light;
}					t_colb;

t_light				*new_light(int rgb, float inten, t_vec *origin);
void				transform_lights(t_light *light_lst, t_cam *cam);
t_amb				*new_amb(int rgb, float inten);
t_colb				*new_colb(t_amb *amb);
void				colb_reset(t_colb *colb, t_closest *closest);

#endif
