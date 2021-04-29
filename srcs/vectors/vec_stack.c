/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_stack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 20:08:48 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 22:45:37 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vst	vst_transform(t_vec *vec, float **matrix)
{
	t_vst	vst_transformed;
	float	**vec_homogen;
	float	**homogen_transformed;
	int		i;

	i = 0;
	vec_homogen = get_matrix_rows(1);
	homogen_transformed = get_matrix_rows(1);
	vec_homogen[0][0] = vec->u;
	vec_homogen[0][1] = vec->v;
	vec_homogen[0][2] = vec->n;
	vec_homogen[0][3] = 1;
	while (i < 4)
	{
		homogen_transformed[0][i] = vec_homogen[0][0] * matrix[i][0]
			+ vec_homogen[0][1] * matrix[i][1] + vec_homogen[0][2]
			* matrix[i][2] + vec_homogen[0][3] * matrix[i][3];
		i++;
	}
	vst_transformed = new_vst(homogen_transformed[0][0],
			homogen_transformed[0][1], homogen_transformed[0][2]);
	free_matrix(vec_homogen, 1);
	free_matrix(homogen_transformed, 1);
	return (vst_transformed);
}

t_vst	new_vst(float u, float v, float n)
{
	t_vst	vst;

	vst.u = u;
	vst.v = v;
	vst.n = n;
	return (vst);
}

t_vst	vst_subtract(t_vst vst1, t_vst vst2)
{
	t_vst	result;

	result.u = vst1.u - vst2.u;
	result.v = vst1.v - vst2.v;
	result.n = vst1.n - vst2.n;
	return (result);
}

t_vst	vst_cross(t_vst vst1, t_vst vst2)
{
	t_vst	result;

	result.u = (vst1.v * vst2.n) - (vst2.v * vst1.n);
	result.v = (vst2.u * vst1.n) - (vst1.u * vst2.n);
	result.n = (vst1.u * vst2.v) - (vst2.u * vst1.v);
	return (result);
}

t_vst	vst_norm_check(t_vst normal)
{
	t_vst	pos_norm;
	float	length;

	length = vst_length(normal);
	pos_norm.u = normal.u / length;
	pos_norm.v = normal.v / length;
	pos_norm.n = normal.n / length;
	pos_norm.u = pos_norm.n < 0 ? pos_norm.u * (-1) : pos_norm.u;
	pos_norm.v = pos_norm.n < 0 ? pos_norm.v * (-1) : pos_norm.v;
	pos_norm.n = pos_norm.n < 0 ? pos_norm.n * (-1) : pos_norm.n;
	return (pos_norm);
}
