/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_triang.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:54:13 by lessie            #+#    #+#             */
/*   Updated: 2021/02/17 12:27:24 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	inter_triang(t_vec *orig, t_vec *dir, t_triang *triang)
{
	t_vec	*d_vec;
	t_vec	*p_vec;
	t_vec	*q_vec;
	float	det;
	float	baryc_u;
	float	baryc_v;
	float	dist;
	float   inv_det;

	p_vec = vec_cross(dir, triang->edge_2);
	det = dot_product(triang->edge_1, p_vec);
	if (det > -MIN && det < MIN)
		return (0);
	inv_det = 1.0 / det;
	d_vec = vec_subtract(orig, triang->vert_1);
	baryc_u = inv_det * dot_product(d_vec, p_vec);
	if (baryc_u < 0.0 || baryc_u > 1.0)
		return (0);
	q_vec = vec_cross(d_vec, triang->edge_1);
	baryc_v = inv_det * dot_product(dir, q_vec);
	if (baryc_v < 0.0 || (baryc_u + baryc_v) > 1.0)
		return (0);
	dist = inv_det * dot_product(triang->edge_2, q_vec);
	if (dist > 0)
		return (dist);
	return (0);
}
