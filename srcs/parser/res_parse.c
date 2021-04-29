/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:49:39 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 18:24:03 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		res_parse(t_scene *scene, const char *line)
{
	int		i;
	int		x;
	int		y;

	i = 1;
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(ft_atoi(&line[i], &x, &i)))
		return (0);
	if (!(check_eat_space(&line[i], &i)))
		return (0);
	if (!(ft_atoi(&line[i], &y, &i)))
		return (0);
	if (!(check_end_line(&line[i])))
		return (0);
	return (check_append_res(scene, x, y));
}

int		check_append_res(t_scene *scene, int x, int y)
{
	if (scene->resolution_x)
		return (0);
	if (x <= 0 || y <= 0)
		return (0);
	scene->resolution_x = x * 1.0;
	scene->resolution_y = y * 1.0;
	return (1);
}
