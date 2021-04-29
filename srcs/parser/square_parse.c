/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:38:42 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 18:45:41 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		square_parse(t_scene *scene, const char *line)
{
	int		i;
	float	vector[6];
	int		rgb;
	float	side_size;
	float	length;

	i = 2;
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(parse_vec(&line[i], vector, 2, &i)))
		return (0);
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(ft_atof(&line[i], &side_size, &i)))
		return (0);
	if (side_size <= 0)
		return (0);
	length = side_size / 2.0;
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(parse_rgb(&line[i], &rgb, &i)))
		return (0);
	if (!(check_end_line(&line[i])))
		return (0);
	return (check_append_square(scene, vector, length, rgb));
}

int		check_append_square(t_scene *scene, float *vector,
		float length, int rgb)
{
	t_vec		*center;
	t_vec		*normal;
	t_triang	*triang;
	t_triang	*tmp;
	t_vec		**sq_v;

	center = new_vec(vector[0], vector[1], vector[2]);
	normal = new_vec(vector[3], vector[4], vector[5]);
	sq_v = get_sq_vert(normal, length);
	triang = new_triang(vec_addition(sq_v[0], center), vec_addition(
				sq_v[1], center), vec_addition(sq_v[2], center), rgb);
	triang->next = new_triang(vec_addition(sq_v[0], center), vec_addition(
				sq_v[2], center), vec_addition(sq_v[3], center), rgb);
	tmp = scene->tr_lst;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	if (tmp)
		tmp->next = triang;
	else
		scene->tr_lst = triang;
	free(center);
	free(normal);
	free_sq_vert(sq_v);
	return (1);
}

t_vec	**get_sq_vert(t_vec *normal, float length)
{
	t_vec	*tmp;
	t_vec	*norm_x;
	t_vec	*norm_y;
	t_vec	**result;

	vec_normalize(normal);
	normal->u = normal->n < 0 ? normal->u * (-1) : normal->u;
	normal->v = normal->n < 0 ? normal->v * (-1) : normal->v;
	normal->n = normal->n < 0 ? normal->n * (-1) : normal->n;
	if ((normal->v == 1) || (normal->v == -1))
		tmp = (normal->v == 1) ? new_vec(1, 0, 0) : new_vec(-1, 0, 0);
	else
		tmp = new_vec(0, 1, 0);
	norm_x = vec_cross(tmp, normal);
	vec_normalize(norm_x);
	norm_y = vec_cross(normal, norm_x);
	result = get_sq_edges(norm_x, norm_y, length);
	free(norm_x);
	free(norm_y);
	free(tmp);
	return (result);
}

t_vec	**get_sq_edges(t_vec *norm_x, t_vec *norm_y, float length)
{
	t_vec	**result;
	t_vec	*min_x;
	t_vec	*plus_x;
	t_vec	*min_y;
	t_vec	*plus_y;

	if (!(result = malloc(sizeof(t_vec *) * 4)))
		error_exit(-2);
	min_x = vec_multipl_on(norm_x, (length * (-1.0)));
	plus_x = vec_multipl_on(norm_x, length);
	min_y = vec_multipl_on(norm_y, (length * (-1.0)));
	plus_y = vec_multipl_on(norm_y, length);
	result[0] = vec_addition(min_x, min_y);
	result[1] = vec_addition(min_x, plus_y);
	result[2] = vec_addition(plus_x, plus_y);
	result[3] = vec_addition(plus_x, min_y);
	free(min_x);
	free(plus_x);
	free(min_y);
	free(plus_y);
	return (result);
}

void	free_sq_vert(t_vec **sq_vertices)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		free(sq_vertices[i]);
		i++;
	}
	free(sq_vertices);
}
