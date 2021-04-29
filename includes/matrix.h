/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:20:58 by lessie            #+#    #+#             */
/*   Updated: 2021/04/27 14:35:37 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

float	**get_matrix_rows(int rows);
float	**matrix_multiply(float **left_matrix, float **right_matrix, int rows);
t_vec	*vec_transform(t_vec *vec, float **matrix);
void	free_matrix(float **matrix, int rows);

#endif
