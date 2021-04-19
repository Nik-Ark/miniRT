/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:35:43 by lessie            #+#    #+#             */
/*   Updated: 2021/02/17 12:35:47 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		main(int argc, char **argv)
{
    int     save;
    int     fd;
    void	*mlx;
    void	*window;
    t_scene *scene;

    if (argc < 2 || argc > 3)
        error_exit(-1);
    save = 0;
    if (argc == 3 && !(save = ft_strcmp(argv[2], "--save")))
        error_exit(-6);
    fd = open_fd(argv[1]);
    scene = parsing(fd);
    transform_scene(scene, scene->cam_lst);

    if (save)
        create_bmp(scene, argv[1]);
    else                                            // Whole else block also will go into one function
    {
        if (!(mlx = mlx_init()))
            error_exit(-3);
        if (!(window = mlx_new_window(mlx, scene->resolution_x, scene->resolution_y, "miniRT")))
            error_exit(-4);
        ray_tracing(mlx, window, scene);
        mlx_loop(mlx);
        free(mlx);
        free(window);
    }
    //free_scene(scene);
	return (0);
}
