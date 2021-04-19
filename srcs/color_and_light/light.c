/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 12:10:44 by lessie            #+#    #+#             */
/*   Updated: 2021/02/15 17:04:16 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light		*new_light(int rgb, float inten, t_vec *origin)
{
	t_light		*light;

	light = malloc(sizeof(t_light));
	if (!light)
		error_exit(-2);
	light->rgb = rgb;
	light->inten = inten;
	light->origin_w = origin;
    light->origin = new_vec(0,0,0);
	light->next = NULL;
	return (light);
}

void        transform_lights(t_light *light_lst, t_cam *cam)
{
    t_light     *tmp;

    tmp = light_lst;
    while (tmp)
    {
        free(tmp->origin);
        //printf("Light before: u = %f v = %f n = %f\n", tmp->origin->u, tmp->origin->v, tmp->origin->n);
        tmp->origin = vec_transform(tmp->origin_w, cam->matrix_w_to_cam);
        //printf("Light after: u = %f v = %f n = %f\n", tmp->origin->u, tmp->origin->v, tmp->origin->n);
        tmp = tmp->next;
    }
}

t_amb		*new_amb(int rgb, float inten)
{
	t_amb	*amb;

	amb = malloc(sizeof(t_amb));
	if (!amb)
		error_exit(-2);
	amb->rgb = rgb;
	amb->inten = inten;
	return (amb);
}

t_colb		*new_colb(t_amb *amb)
{
	t_colb	*colb;
	int		amb_rgb;
	float	r;
	float	g;
	float	b;

	colb = malloc(sizeof(t_colb));
	if (!colb)
		error_exit(-2);
	amb_rgb = amb->rgb;
	r = get_r(amb_rgb);
	g = get_g(amb_rgb);
	b = get_b(amb_rgb);
	r *= amb->inten;
	g *= amb->inten;
	b *= amb->inten;
	colb->surf_p = NULL;     // CREATE
	colb->surf_norm = NULL; //  NEW
	colb->to_light = NULL; //   0,0,0 VEC ???
	colb->dist_to_light = 0;
	colb->amb = new_vec(r, g, b); //FREE_SCENE
	colb->rgb = new_vec(0, 0, 0); //FREE_SCENE
	return (colb);
}

void		colb_reset(t_colb *colb)
{
	free(colb->surf_p);
	free(colb->surf_norm);
	colb->rgb->u = 0;
	colb->rgb->v = 0;
	colb->rgb->n = 0;
}
