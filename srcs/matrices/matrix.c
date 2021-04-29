/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:24:11 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:34:25 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	**get_matrix_rows(int rows)
{
	float	**zeroed_matrix;
	int		i;
	int		j;

	zeroed_matrix = malloc(sizeof(float *) * rows);
	if (!zeroed_matrix)
		error_exit(-2);
	i = 0;
	while (i < rows)
	{
		zeroed_matrix[i] = malloc(sizeof(float) * 4);
		if (!zeroed_matrix[i])
			error_exit(-2);
		j = 0;
		while (j < 4)
		{
			zeroed_matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	return (zeroed_matrix);
}

float	**matrix_multiply(float **right_matrix, float **left_matrix, int rows)
{
	float	**result_matrix;
	int		i;
	int		j;

	result_matrix = get_matrix_rows(rows);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < 4)
		{
			result_matrix[i][j] = (left_matrix[i][0] * right_matrix[0][j])
				+ (left_matrix[i][1] * right_matrix[1][j])
				+ (left_matrix[i][2] * right_matrix[2][j])
				+ (left_matrix[i][3] * right_matrix[3][j]);
			j++;
		}
		i++;
	}
	return (result_matrix);
}

t_vec	*vec_transform(t_vec *vec, float **matrix)
{
	t_vec	*vec_transformed;
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
	vec_transformed = new_vec(homogen_transformed[0][0],
			homogen_transformed[0][1], homogen_transformed[0][2]);
	free_matrix(vec_homogen, 1);
	free_matrix(homogen_transformed, 1);
	return (vec_transformed);
}

void	free_matrix(float **matrix, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
