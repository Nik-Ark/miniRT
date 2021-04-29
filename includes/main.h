/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:34:34 by lessie            #+#    #+#             */
/*   Updated: 2021/04/28 17:15:38 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "camera.h"
# include "scene.h"

typedef struct	s_mypar
{
	void		*mlx;
	void		*window;
	t_scene		*scene;

}				t_mypar;

int				main(int argc, char **argv);
void			run_window(const char *filename_rt);
int				key_actions(int key_code, t_mypar *par);
int				cam_list_thing(int key_code, t_scene *scene);
int				close_minirt(void);

#endif
