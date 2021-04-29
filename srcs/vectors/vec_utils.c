/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 20:35:27 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 22:50:17 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_two(t_vec *vec_1, t_vec *vec_2)
{
	free(vec_1);
	free(vec_2);
}

t_vec	*sphere_norm(t_vec *hit, t_vec *center)
{
	t_vec	*norm;

	norm = vec_subtract(hit, center);
	vec_normalize(norm);
	norm->u = norm->n < 0 ? norm->u * (-1) : norm->u;
	norm->v = norm->n < 0 ? norm->v * (-1) : norm->v;
	norm->n = norm->n < 0 ? norm->n * (-1) : norm->n;
	return (norm);
}
