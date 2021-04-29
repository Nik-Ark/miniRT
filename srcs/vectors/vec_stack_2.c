/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_stack_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 12:48:25 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 22:48:29 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vst_length(t_vst vst)
{
	float	result;

	result = vst.u * vst.u + vst.v * vst.v + vst.n * vst.n;
	result = sqrt(result);
	return (result);
}

float	dot_vst(t_vst vst1, t_vst vst2)
{
	float	result;

	result = vst1.u * vst2.u + vst1.v * vst2.v + vst1.n * vst2.n;
	return (result);
}

t_vst	vst_multipl_on(t_vst vst, float value)
{
	t_vst	result;

	result.u = vst.u * value;
	result.v = vst.v * value;
	result.n = vst.n * value;
	return (result);
}

t_vst	vst_addition(t_vst vst1, t_vst vst2)
{
	t_vst	result;

	result.u = vst1.u + vst2.u;
	result.v = vst1.v + vst2.v;
	result.n = vst1.n + vst2.n;
	return (result);
}
