/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:57:50 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 22:52:05 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float		dot_product(t_vec *vec1, t_vec *vec2)
{
	float	result;

	result = vec1->u * vec2->u + vec1->v * vec2->v + vec1->n * vec2->n;
	return (result);
}

float		vec_length(t_vec *vec)
{
	float	result;

	result = vec->u * vec->u + vec->v * vec->v + vec->n * vec->n;
	result = sqrt(result);
	return (result);
}

void		vec_normalize(t_vec *vec)
{
	float	length;

	length = vec_length(vec);
	vec->u = vec->u / length;
	vec->v = vec->v / length;
	vec->n = vec->n / length;
}

t_vec		*vec_reflect(t_vec *surf_p, t_vec *norm)
{
	t_vec	*multiplyer;
	t_vec	*reflected;

	multiplyer = vec_multipl_on(norm, 2 * dot_product(surf_p, norm));
	reflected = vec_subtract(multiplyer, surf_p);
	free(multiplyer);
	return (reflected);
}

t_vec		*vec_cross(t_vec *vec1, t_vec *vec2)
{
	t_vec	*result;

	result = malloc(sizeof(t_vec));
	if (!result)
		error_exit(-2);
	result->u = (vec1->v * vec2->n) - (vec2->v * vec1->n);
	result->v = (vec2->u * vec1->n) - (vec1->u * vec2->n);
	result->n = (vec1->u * vec2->v) - (vec2->u * vec1->v);
	return (result);
}
