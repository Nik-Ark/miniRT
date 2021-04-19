/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:53:36 by lessie            #+#    #+#             */
/*   Updated: 2021/04/02 14:54:07 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAM_PARSE_H
# define CAM_PARSE_H

int     cam_parse(t_scene **scene, const char *line);
int     check_append_cam(t_scene **scene, float *vectors, int fov);

#endif
