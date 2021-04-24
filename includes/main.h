/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:34:34 by lessie            #+#    #+#             */
/*   Updated: 2021/04/22 13:35:08 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

#include "camera.h"
#include "scene.h"

typedef struct      s_node
{
    void            *mlx;
    void            *window;
    t_scene         *scene;

}                   t_node;

void    run_window(t_node *node);
int     key_actions(int key_code, t_node *node);
int     cam_list_thing(int key_code, t_scene *scene);
int     close_minirt();

#endif
