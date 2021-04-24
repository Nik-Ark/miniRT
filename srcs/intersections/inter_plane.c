/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 10:54:22 by lessie            #+#    #+#             */
/*   Updated: 2021/02/17 08:06:05 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	inter_plane(t_vec *origin, t_vec *dir, t_plane *plane)
{
	float	proect;
	float	dist;
	float	denom;

	dist = 0;
	denom = dot_product(plane->normal, dir);
	proect = dot_product(origin, plane->normal) - dot_product(plane->normal, plane->center);
	if (denom < MIN && denom > -MIN)
		return (0);
	dist = - (proect / denom);
	//printf("plane dist = %f\n", dist);
	if (dist > 0)
		return (dist);
	return (0);
}
