/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_parse.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:30:05 by lessie            #+#    #+#             */
/*   Updated: 2021/04/07 17:30:41 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_PARSE_H
# define TRIANGLE_PARSE_H

int     triangle_parse(t_scene **scene, const char *line);
int     check_append_triang(t_scene **scene, float *vector, int rgb);

#endif
