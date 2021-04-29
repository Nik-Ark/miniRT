/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:28:05 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 18:21:56 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		plane_parse(t_scene *scene, const char *line)
{
	int		i;
	float	vector[6];
	int		rgb;

	i = 2;
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(parse_vec(&line[i], vector, 2, &i)))
		return (0);
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(parse_rgb(&line[i], &rgb, &i)))
		return (0);
	if (!(check_end_line(&line[i])))
		return (0);
	return (check_append_plane(scene, vector, rgb));
}

int		check_append_plane(t_scene *scene, float *vector, int rgb)
{
	t_vec	*origin;
	t_vec	*norm;
	t_plane	*tmp;

	origin = new_vec(vector[0], vector[1], vector[2]);
	norm = new_vec(vector[3], vector[4], vector[5]);
	vec_normalize(norm);
	tmp = scene->pl_lst;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	if (tmp)
		tmp->next = new_plane(origin, norm, rgb);
	else
		scene->pl_lst = new_plane(origin, norm, rgb);
	return (1);
}
