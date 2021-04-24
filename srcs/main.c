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
    t_scene *scene;
    t_node  *node;

    if (argc < 2 || argc > 3)
        error_exit(-1);
    save = 0;
    node = NULL;
    if (argc == 3 && !(save = ft_strcmp(argv[2], "--save")))
        error_exit(-6);
    fd = open_fd(argv[1]);
    scene = parsing(fd);
    transform_scene(scene, scene->cam_lst);
    if (save)
        create_bmp(scene, argv[1]);
    else
    {
        node = create_node(&scene);
        run_window(node);
    }
	return (0);
}

t_node  *create_node(t_scene **scene)
{
    t_node  *node;

    node = malloc(sizeof(t_node *));
    if (node == NULL)
        error_exit(-2);
    node->mlx = mlx_init();
    if (node->mlx == NULL)
        error_exit(-3);
    node->window = mlx_new_window(node->mlx, (int)(*scene)->resolution_x, (int)(*scene)->resolution_y, "miniRT");
    if (node->window == NULL)
        error_exit(-4);
    node->scene = (*scene);
    return (node);
}

void    run_window(t_node *node)
{
    t_scene *scene;
    t_cam   *curr_cam;

    scene = node->scene;
    curr_cam = scene->cam_lst;

    curr_cam->img = create_image(node->mlx, scene);
    mlx_put_image_to_window(node->mlx, node->window, curr_cam->img, 0, 0);

    mlx_key_hook(node->window, key_actions, &*node);
    mlx_hook(node->window, 17, (1L << 0), close_minirt, node);
    mlx_loop(node->mlx);
}

int     key_actions(int key_code, t_node *node)
{
    if (key_code == 53)
        close_minirt();
    if (key_code == 123 || key_code == 124)
    {
        if (cam_list_thing(key_code, node->scene))
        {
            mlx_clear_window(node->mlx, node->window);
            if (node->scene->cam_lst->img == NULL)
            {
                write(1, "Creating image...\n", 19);
                transform_scene(node->scene, node->scene->cam_lst);
                node->scene->cam_lst->img = create_image(node->mlx, node->scene);
            }
            mlx_put_image_to_window(node->mlx, node->window, node->scene->cam_lst->img, 0, 0);
        }
    }
    return (0);
}

int     cam_list_thing(int key_code, t_scene *scene)
{
    if (key_code == 124)
    {
        if (scene->cam_lst->next)
        {
            write(1, "NEXT CAMERA\n", 13);
            scene->cam_lst = scene->cam_lst->next;
            return (1);
        }
        else
        {
            write(1, "CURRENT CAMERA IS LAST\n", 24);
            return (0);
        }
    }
    if (key_code == 123)
    {
        if (scene->cam_lst->prev)
        {
            write(1, "PREVIOUS CAMERA\n", 17);
            scene->cam_lst = scene->cam_lst->prev;
            return (1);
        }
        else
        {
            write(1, "CURRENT CAMERA IS FIRST\n", 25);
            return (0);
        }
    }
    return (0);
}

int     close_minirt()
{
    exit(0);
}