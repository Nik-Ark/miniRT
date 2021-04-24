/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_parse.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 12:39:20 by lessie            #+#    #+#             */
/*   Updated: 2021/04/20 12:40:05 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_PARSE_H
# define SQUARE_PARSE_H

int     square_parse(t_scene **scene, const char *line);
int     check_append_square(t_scene **scene, float *vector, float side_size, int rgb);
t_vec	**get_sq_vert(t_vec *normal, float length);
t_vec	**get_sq_edges(t_vec *norm_x, t_vec *norm_y, float length);
void	free_sq_vert(t_vec **sq_vertices);

#endif
