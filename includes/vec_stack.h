/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_stack.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 20:09:32 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:16:36 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_STACK_H
# define VEC_STACK_H

typedef struct	s_vst
{
	float	u;
	float	v;
	float	n;
}				t_vst;

t_vst			vst_transform(t_vec *vec, float **matrix);
t_vst			new_vst(float u, float v, float n);
t_vst			vst_subtract(t_vst vst1, t_vst vst2);
t_vst			vst_cross(t_vst vst1, t_vst vst2);
t_vst			vst_norm_check(t_vst normal);
float			vst_length(t_vst vst);
float			dot_vst(t_vst vst1, t_vst vst2);
t_vst			vst_multipl_on(t_vst vst, float value);
t_vst			vst_addition(t_vst vst1, t_vst vst2);

#endif
