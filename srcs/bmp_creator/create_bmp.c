/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:21:52 by lessie            #+#    #+#             */
/*   Updated: 2021/04/29 16:23:41 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void				create_bmp(const char *filename_rt)
{
	int				fd;
	t_scene			*scene;
	char			*filename;
	int				padding;
	int				num_of_bytes;

	fd = open_fd(filename_rt);
	scene = parsing(fd);
	padding = (4 - ((int)(scene->resolution_x * 3) % 4)) % 4;
	num_of_bytes = (scene->resolution_x
			* scene->resolution_y * 3) + (padding * scene->resolution_y) + 54;
	transform_scene(scene, scene->cam_lst);
	filename = get_filename(filename_rt);
	if ((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0655)) <= 0)
		error_exit(10);
	write(1, "Creating ", 9);
	ft_putstr(filename, 1);
	write(1, "\n", 1);
	write_first_header(num_of_bytes, fd);
	write_second_header((int)scene->resolution_x, (int)scene->resolution_y, fd);
	write_pixels(scene, padding, fd);
	close(fd);
	ft_putstr(filename, 1);
	write(1, " successfully created!\nGood Bye!\n", 33);
	exit(0);
}

char				*get_filename(const char *file)
{
	char			*filename;
	int				i;

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
	if (!(filename = malloc(sizeof(char) * (4 + (i += 1)))))
		error_exit(-2);
	filename[i + 3] = '\0';
	filename[i + 2] = 'p';
	filename[i + 1] = 'm';
	filename[i] = 'b';
	while (--i >= 0)
		filename[i] = file[i];
	return (filename);
}

void				write_first_header(int num_of_bytes, int fd)
{
	unsigned char	header[14];
	int				i;

	i = 0;
	while (i < 14)
		header[i++] = (unsigned char)(0);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(num_of_bytes);
	header[3] = (unsigned char)(num_of_bytes >> 8);
	header[4] = (unsigned char)(num_of_bytes >> 16);
	header[5] = (unsigned char)(num_of_bytes >> 24);
	header[10] = (unsigned char)(54);
	write(fd, header, 14);
}

void				write_second_header(int res_x, int res_y, int fd)
{
	unsigned char	header[40];
	int				i;

	i = 0;
	while (i < 40)
		header[i++] = (unsigned char)(0);
	header[0] = (unsigned char)(40);
	header[4] = (unsigned char)(res_x);
	header[5] = (unsigned char)(res_x >> 8);
	header[6] = (unsigned char)(res_x >> 16);
	header[7] = (unsigned char)(res_x >> 24);
	header[8] = (unsigned char)(res_y);
	header[9] = (unsigned char)(res_y >> 8);
	header[10] = (unsigned char)(res_y >> 16);
	header[11] = (unsigned char)(res_y >> 24);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(24);
	write(fd, header, 40);
}

void				write_pixels(t_scene *scene, int padding, int fd)
{
	int				color;
	t_vplane		*vplane;
	t_closest		*closest;
	float			y;
	float			x;

	vplane = get_vplane(scene->resolution_x,
			scene->resolution_y, scene->cam_lst->fov);
	closest = new_closest();
	y = -1;
	while (++y < scene->resolution_y)
	{
		x = -1;
		while (++x < scene->resolution_x)
		{
			canvas_to_vplane(y, x, closest, vplane);
			color = all_intersects(closest, scene);
			put_pixel(color, fd);
			if (x == scene->resolution_x && padding)
				add_padding(padding, fd);
		}
	}
	free(vplane);
	free(closest);
}
