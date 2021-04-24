/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:25:26 by lessie            #+#    #+#             */
/*   Updated: 2021/02/12 12:47:55 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct	s_vec
{
	float		u;
	float		v;
	float		n;
}				t_vec;

t_vec			*new_vec(float u, float v, float n);
t_vec			*vec_subtract(t_vec *vec1, t_vec *vec2);
t_vec			*vec_addition(t_vec *vec1, t_vec *vec2);
t_vec			*vec_multipl_on(t_vec *vec1, float value);
t_vec			*vec_divide_on(t_vec *vec1, float value);
float			dot_product(t_vec *vec1, t_vec *vec2);
float			vec_length(t_vec *vec);
void			vec_normalize(t_vec *vec);
t_vec			*vec_reflect(t_vec *surf_p, t_vec *norm);
t_vec			*vec_cross(t_vec *vec1, t_vec *vec2);

#endif
