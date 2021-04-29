/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:35:43 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 23:32:15 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		main(int argc, char **argv)
{
	int		save;

	if (argc < 2 || argc > 3)
		error_exit(-1);
	save = 0;
	if (argc == 3 && !(save = ft_strcmp(argv[2], "--save")))
		error_exit(-6);
	if (save)
	{
		write(1, "Parsing file descriptor...\n", 27);
		create_bmp(argv[1]);
	}
	else
	{
		write(1, "Parsing file descriptor...\n", 27);
		run_window(argv[1]);
	}
	return (0);
}

void	run_window(const char *filename_rt)
{
	int		fd;
	t_mypar	par;

	fd = open_fd(filename_rt);
	par.scene = parsing(fd);
	if (!(par.mlx = mlx_init()))
		error_exit(-3);
	par.scene->resolution_x = par.scene->resolution_x > 2560.0 ? 2560.0
		: par.scene->resolution_x;
	par.scene->resolution_y = par.scene->resolution_y > 2560.0 ? 1440.0
		: par.scene->resolution_y;
	if (!(par.window = mlx_new_window(par.mlx, (int)par.scene->resolution_x,
					(int)par.scene->resolution_y, "miniRT")))
		error_exit(-4);
	write(1, "Creating image...\n", 18);
	transform_scene(par.scene, par.scene->cam_lst);
	par.scene->cam_lst->img = create_image(par.mlx, par.scene);
	write(1, "Image created\n", 14);
	mlx_put_image_to_window(par.mlx, par.window, par.scene->cam_lst->img, 0, 0);
	mlx_key_hook(par.window, key_actions, &par);
	mlx_hook(par.window, 17, (1L << 0), close_minirt, &par);
	mlx_loop(par.mlx);
}

int		key_actions(int key_code, t_mypar *par)
{
	if (key_code == 53)
		close_minirt();
	if (key_code == 123 || key_code == 124)
	{
		if (cam_list_thing(key_code, par->scene))
		{
			mlx_clear_window(par->mlx, par->window);
			if (par->scene->cam_lst->img == NULL)
			{
				write(1, "Creating image...\n", 18);
				transform_scene(par->scene, par->scene->cam_lst);
				par->scene->cam_lst->img = create_image(par->mlx,
						par->scene);
				write(1, "Image created\n", 14);
			}
			mlx_put_image_to_window(par->mlx, par->window,
					par->scene->cam_lst->img, 0, 0);
		}
	}
	return (0);
}

int		cam_list_thing(int key_code, t_scene *scene)
{
	if (key_code == 124)
	{
		if (scene->cam_lst->next)
		{
			write(1, "NEXT CAMERA\n", 12);
			scene->cam_lst = scene->cam_lst->next;
			return (1);
		}
		else
			write(1, "CURRENT CAMERA IS LAST\n", 23);
	}
	if (key_code == 123)
	{
		if (scene->cam_lst->prev)
		{
			write(1, "PREVIOUS CAMERA\n", 16);
			scene->cam_lst = scene->cam_lst->prev;
			return (1);
		}
		else
			write(1, "CURRENT CAMERA IS FIRST\n", 24);
	}
	return (0);
}

int		close_minirt(void)
{
	write(1, "Good Bye!\n", 10);
	exit(0);
}
