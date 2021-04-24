/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:29:06 by lessie            #+#    #+#             */
/*   Updated: 2021/04/07 17:29:52 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_PARSE_H
# define PLANE_PARSE_H

int     plane_parse(t_scene **scene, const char *line);
int     check_append_plane(t_scene **scene, float *vector, int rgb);

#endif
