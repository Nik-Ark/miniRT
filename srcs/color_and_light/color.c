/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:08:09 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:26:14 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int		get_r(int rgb)
{
	int		result;

	result = (rgb & (255 << 16));
	return (result >> 16);
}

int		get_g(int rgb)
{
	int		result;

	result = (rgb & (255 << 8));
	return (result >> 8);
}

int		get_b(int rgb)
{
	return (rgb & 255);
}

void	add_color(t_colb *colb, t_light *light, float angle, float mult)
{
	colb->rgb->u += mult * ((light->inten / (colb->dist_to_light
					* colb->dist_to_light)) * angle) * get_r(light->rgb);
	colb->rgb->v += mult * ((light->inten / (colb->dist_to_light
					* colb->dist_to_light)) * angle) * get_g(light->rgb);
	colb->rgb->n += mult * ((light->inten / (colb->dist_to_light
					* colb->dist_to_light)) * angle) * get_b(light->rgb);
}
