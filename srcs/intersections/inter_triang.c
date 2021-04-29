/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_triang.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:54:13 by lessie            #+#    #+#             */
/*   Updated: 2021/04/27 20:25:02 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	inter_triang(t_vst orig, t_vst dir, t_triang *triang)
{
	t_vst	vec[3];
	float	baryc[2];
	float	det;
	float	dist;
	float	inv_det;

	vec[0] = vst_cross(dir, triang->edge_2);
	det = dot_vst(triang->edge_1, vec[0]);
	if (det > -MIN && det < MIN)
		return (0);
	inv_det = 1.0 / det;
	vec[1] = vst_subtract(orig, triang->vert_1);
	baryc[0] = inv_det * dot_vst(vec[1], vec[0]);
	if (baryc[0] < 0.0 || baryc[0] > 1.0)
		return (0);
	vec[2] = vst_cross(vec[1], triang->edge_1);
	baryc[1] = inv_det * dot_vst(dir, vec[2]);
	if (baryc[1] < 0.0 || (baryc[0] + baryc[1]) > 1.0)
		return (0);
	dist = inv_det * dot_vst(triang->edge_2, vec[2]);
	if (dist > 0)
		return (dist);
	return (0);
}
