/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:52:07 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 18:03:28 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		cylinder_parse(t_scene *scene, const char *line)
{
	int		i;
	float	vector[6];
	float	diam_height[2];
	int		rgb;

	i = 2;
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(parse_vec(&line[i], vector, 2, &i)))
		return (0);
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(ft_atof(&line[i], &diam_height[0], &i)))
		return (0);
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(ft_atof(&line[i], &diam_height[1], &i)))
		return (0);
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(parse_rgb(&line[i], &rgb, &i)))
		return (0);
	if (!(check_end_line(&line[i])))
		return (0);
	return (check_append_cyl(scene, vector, diam_height, rgb));
}

int		check_append_cyl(t_scene *scene, float *vector,
		float *diam_height, int rgb)
{
	t_vec	*bottom;
	t_vec	*orient;
	t_cyl	*tmp;

	if (diam_height[0] <= 0 || diam_height[1] <= 0)
		return (0);
	diam_height[0] /= 2.0;
	bottom = new_vec(vector[0], vector[1], vector[2]);
	orient = new_vec(vector[3], vector[4], vector[5]);
	vec_normalize(orient);
	tmp = scene->cyl_lst;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	if (tmp)
		tmp->next = new_cylinder(bottom, orient, diam_height, rgb);
	else
		scene->cyl_lst = new_cylinder(bottom, orient, diam_height, rgb);
	return (1);
}
