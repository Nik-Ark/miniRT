/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parse.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lessie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:55:47 by lessie            #+#    #+#             */
/*   Updated: 2021/04/27 14:46:36 by lessie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_PARSE_H
# define SPHERE_PARSE_H

int		sphere_parse(t_scene *scene, const char *line);
int		check_append_sphere(t_scene *scene, float *vector, float diam, int rgb);

#endif
