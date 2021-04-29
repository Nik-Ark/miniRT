/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:48:04 by lessie            #+#    #+#             */
/*   Updated: 2021/04/29 14:00:33 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		open_fd(const char *file)
{
	int		fd;
	int		i;

	if ((fd = open(file, O_RDONLY)) <= 0)
		error_exit(-5);
	i = 0;
	while (file[i] != '.' && file[i])
		i++;
	while ((file[i] == '.' && file[i + 1] == '/') || (file[i] == '.'
	&& file[i + 1] == '.' && file[i + 2] == '/'))
	{
		if (file[i] == '.' && file[i + 1] == '/')
			i += 2;
		if (file[i] == '.' && file[i + 1] == '.' && file[i + 2] == '/')
			i += 3;
		while (file[i] != '.' && file[i])
			i++;
	}
	if (!i)
		error_exit(-7);
	if (!(ft_strcmp(&file[i], ".rt")))
		error_exit(-8);
	return (fd);
}

t_scene	*parsing(int fd)
{
	int		ret;
	t_scene	*scene;
	char	*line;
	int		i;

	line = NULL;
	i = 1;
	scene = new_scene();
	while ((ret = get_next_line(fd, &line)))
	{
		if (!(parse_line(scene, line)))
			explicit_err(line, i);
		free(line);
		i++;
	}
	if (ret < 0 || !(parse_line(scene, line)))
		explicit_err(line, i);
	free(line);
	close(fd);
	check_scene(scene);
	return (scene);
}

int		parse_line(t_scene *scene, const char *line)
{
	if (line[0] == '\0')
		return (1);
	if (line[0] == '#')
		return (1);
	if (line[0] == 'R')
		return (res_parse(scene, line));
	if (line[0] == 'A')
		return (amb_parse(scene, line));
	if (line[0] == 'c' && line[1] == 'y')
		return (cylinder_parse(scene, line));
	if (line[0] == 'c')
		return (cam_parse(scene, line));
	if (line[0] == 'l')
		return (light_parse(scene, line));
	if (line[0] == 's' && line[1] == 'p')
		return (sphere_parse(scene, line));
	if (line[0] == 'p' && line[1] == 'l')
		return (plane_parse(scene, line));
	if (line[0] == 't' && line[1] == 'r')
		return (triangle_parse(scene, line));
	if (line[0] == 's' && line[1] == 'q')
		return (square_parse(scene, line));
	return (0);
}

int		parse_rgb(const char *line, int *rgb, int *i)
{
	int		nums;
	int		j;
	int		r;
	int		g;
	int		b;

	j = 0;
	nums = 2;
	if (!(ft_atoi(line, &r, &j)))
		return (0);
	if (!(num_coma(&line[j], &j, &nums)))
		return (0);
	if (!(ft_atoi(&line[j], &g, &j)))
		return (0);
	if (!(num_coma(&line[j], &j, &nums)))
		return (0);
	if (!(ft_atoi(&line[j], &b, &j)))
		return (0);
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		return (0);
	*rgb = create_rgb(r, g, b);
	*i += j;
	return (nums == 0 ? 1 : 0);
}
