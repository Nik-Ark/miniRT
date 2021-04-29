/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:49:15 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:54:48 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		cam_parse(t_scene *scene, const char *line)
{
	int		i;
	int		fov;
	float	vectors[6];

	i = 1;
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(parse_vec(&line[i], vectors, 2, &i)))
		return (0);
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(ft_atoi(&line[i], &fov, &i)))
		return (0);
	if (!(check_end_line(&line[i])))
		return (0);
	return (check_append_cam(scene, vectors, fov));
}

int		check_append_cam(t_scene *scene, float *vectors, int fov)
{
	t_vec	*origin;
	t_vec	*dir;
	t_cam	*tmp;
	float	cam_fov;

	if (fov <= 0 || fov > 180)
		return (0);
	tmp = scene->cam_lst;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	cam_fov = fov * 1.0;
	origin = new_vec(vectors[0], vectors[1], vectors[2]);
	dir = new_vec(vectors[3], vectors[4], vectors[5]);
	if (tmp)
	{
		tmp->next = new_cam(origin, dir, cam_fov);
		tmp->next->prev = tmp;
	}
	else
		scene->cam_lst = new_cam(origin, dir, cam_fov);
	return (1);
}
