/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:28:32 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 18:50:26 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		triangle_parse(t_scene *scene, const char *line)
{
	int		i;
	float	vector[9];
	int		rgb;

	i = 2;
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(parse_vec(&line[i], vector, 3, &i)))
		return (0);
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(parse_rgb(&line[i], &rgb, &i)))
		return (0);
	if (!(check_end_line(&line[i])))
		return (0);
	return (check_append_triang(scene, vector, rgb));
}

int		check_append_triang(t_scene *scene, float *vector, int rgb)
{
	t_vec		*vert_1;
	t_vec		*vert_2;
	t_vec		*vert_3;
	t_triang	*tmp;

	vert_1 = new_vec(vector[0], vector[1], vector[2]);
	vert_2 = new_vec(vector[3], vector[4], vector[5]);
	vert_3 = new_vec(vector[6], vector[7], vector[8]);
	tmp = scene->tr_lst;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	if (tmp)
		tmp->next = new_triang(vert_1, vert_2, vert_3, rgb);
	else
		scene->tr_lst = new_triang(vert_1, vert_2, vert_3, rgb);
	return (1);
}
