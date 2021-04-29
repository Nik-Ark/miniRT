/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:23:08 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:33:33 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	inter_cylinder(t_vst orig, t_vst dir, t_cyl *cyl)
{
	float	coeff[3];
	float	dist[2];
	float	result;

	get_coeff(orig, dir, cyl, coeff);
	if (!(cyl_equation(coeff, dist)))
		return (0);
	if (!(result = trim_cyl(orig, dir, cyl, dist)))
		return (0);
	if (result > 0)
		return (result);
	return (0);
}

void	get_coeff(t_vst orig, t_vst dir, t_cyl *cyl, float *coeff)
{
	t_vst	cyl_o;
	t_vst	turn_cyl;
	t_vst	turn_p;
	t_vst	p_orient;
	t_vst	p_cyl;

	cyl_o = vst_multipl_on(cyl->orient, dot_vst(cyl->orient, dir));
	turn_cyl = vst_subtract(orig, cyl->bottom_p);
	turn_p = vst_multipl_on(cyl->orient, dot_vst(cyl->orient, turn_cyl));
	p_orient = vst_subtract(dir, cyl_o);
	p_cyl = vst_subtract(turn_cyl, turn_p);
	coeff[0] = dot_vst(p_orient, p_orient);
	coeff[1] = 2.0 * dot_vst(p_orient, p_cyl);
	coeff[2] = dot_vst(p_cyl, p_cyl) - pow(cyl->radius, 2);
}

int		cyl_equation(const float *coeff, float *dist)
{
	float	discr;
	float	root;

	discr = (coeff[1] * coeff[1]) - (4 * coeff[0] * coeff[2]);
	root = 0;
	if (discr < 0)
		return (0);
	if (discr == 0)
	{
		dist[0] = -0.5 * (coeff[1] / coeff[0]);
		dist[1] = -0.5 * (coeff[1] / coeff[0]);
	}
	if (discr > 0)
	{
		root = coeff[1] > 0 ? -0.5 * (coeff[1] + sqrt(discr)) : -0.5
			* (coeff[1] - sqrt(discr));
		dist[0] = root / coeff[0];
		dist[1] = coeff[2] / root;
	}
	return (1);
}

float	trim_cyl(t_vst orig, t_vst dir, t_cyl *cyl, const float *dist)
{
	float	closest;

	closest = dist[0] > dist[1] ? dist[1] : dist[0];
	if (closest < 0 || !(in_height(orig, dir, cyl, closest)))
	{
		closest = dist[1] > dist[0] ? dist[1] : dist[0];
		if (closest < 0 || !(in_height(orig, dir, cyl, closest)))
			return (0);
	}
	return (closest);
}

int		in_height(t_vst orig, t_vst dir, t_cyl *cyl, float closest)
{
	t_vst	point;
	t_vst	hit_proec;
	t_vst	p_on_height;
	t_vst	normal;
	float	proec_val;

	point = vst_addition(orig, vst_multipl_on(dir, closest));
	hit_proec = vst_subtract(point, cyl->bottom_p);
	proec_val = dot_vst(hit_proec, cyl->orient);
	if (proec_val < 0 || proec_val > cyl->height)
		return (0);
	p_on_height = vst_multipl_on(cyl->orient, proec_val);
	normal = vst_subtract(point, p_on_height);
	cyl->norm = vst_norm_check(normal);
	return (1);
}
