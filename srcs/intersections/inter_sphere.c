/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 00:25:58 by lessie            #+#    #+#             */
/*   Updated: 2021/02/15 17:18:37 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float			inter_sphere(t_vec *origin, t_vec *dir, t_sphere *sphere)
{
	t_vec		*origin_center;
	float		a;
	float		b;
	float		c;
	float		discr;
	float		dist_1;
	float		dist_2;

	origin_center = vec_subtract(origin, sphere->center);
	a = dot_product(dir, dir);
	b = 2 * (dot_product(origin_center, dir));
	c = (dot_product(origin_center, origin_center)) - (sphere->radius * sphere->radius);
	discr = (b * b) - (4 * (a * c));
	free(origin_center);
	if (discr < 0)
		return (0);
	dist_1 = ((b * (-1)) - sqrt(discr)) / (2 * a);
	dist_2 = ((b * (-1)) + sqrt(discr)) / (2 * a);
	if (dist_1 > 0)
		return (dist_1);
	if (dist_2 > 0)
		return (dist_2);
	return (0);
}
