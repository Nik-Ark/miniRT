/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parse.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:52:51 by lessie            #+#    #+#             */
/*   Updated: 2021/04/27 14:25:33 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_PARSE_H
# define CYLINDER_PARSE_H

int		cylinder_parse(t_scene *scene, const char *line);
int		check_append_cyl(t_scene *scene, float *vector,
			float *diam_height, int rgb);

#endif
