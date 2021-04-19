/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 21:14:13 by lessie            #+#    #+#             */
/*   Updated: 2021/02/02 11:18:12 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	*new_vec(float u, float v, float n)
{
	t_vec	*vec;

	vec = malloc(sizeof(t_vec));
	if (!vec)
		error_exit(-2);
	vec->u = u;
	vec->v = v;
	vec->n = n;
	return (vec);
}

t_vec	*vec_subtract(t_vec *vec1, t_vec *vec2)
{
	t_vec	*result;

	result = malloc(sizeof(t_vec));
	if (!result)
		error_exit(-2);
	result->u = vec1->u - vec2->u;
	result->v = vec1->v - vec2->v;
	result->n = vec1->n - vec2->n;
	return (result);
}

t_vec	*vec_addition(t_vec *vec1, t_vec *vec2)
{
	t_vec	*result;

	result = malloc(sizeof(t_vec));
	if (!result)
		error_exit(-2);
	result->u = vec1->u + vec2->u;
	result->v = vec1->v + vec2->v;
	result->n = vec1->n + vec2->n;
	return (result);
}

t_vec	*vec_multipl_on(t_vec *vec1, float value)
{
	t_vec	*result;

	result = malloc(sizeof(t_vec));
	if (!result)
		error_exit(-2);
	result->u = vec1->u * value;
	result->v = vec1->v * value;
	result->n = vec1->n * value;
	return (result);
}

t_vec	*vec_divide_on(t_vec *vec1, float value)
{
	t_vec	*result;

	result = malloc(sizeof(t_vec));
	if (!result)
		error_exit(-2);
	result->u = vec1->u / value;
	result->v = vec1->v / value;
	result->n = vec1->n / value;
	return (result);
}
