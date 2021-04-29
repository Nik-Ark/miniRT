/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 00:25:58 by lessie            #+#    #+#             */
/*   Updated: 2021/04/27 20:08:21 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	inter_sphere(t_vec *origin, t_vec *dir, t_sphere *sphere)
{
	t_vec		*origin_center;
	float		cf[3];
	float		discr;
	float		dist_1;
	float		dist_2;

	origin_center = vec_subtract(origin, sphere->center);
	cf[0] = dot_product(dir, dir);
	cf[1] = 2 * (dot_product(origin_center, dir));
	cf[2] = (dot_product(origin_center, origin_center))
		- (sphere->radius * sphere->radius);
	discr = (cf[1] * cf[1]) - (4 * (cf[0] * cf[2]));
	free(origin_center);
	if (discr < 0)
		return (0);
	dist_1 = ((cf[1] * (-1)) - sqrt(discr)) / (2 * cf[0]);
	dist_2 = ((cf[1] * (-1)) + sqrt(discr)) / (2 * cf[0]);
	if (dist_1 > 0)
		return (dist_1);
	if (dist_2 > 0)
		return (dist_2);
	return (0);
}
